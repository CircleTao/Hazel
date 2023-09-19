#pragma once

#include "Hazel/Core.h"
// 这里一开始会显示无法找到源文件
// 在视频末尾会演示如何修改premake5.lua来新增包含文件夹

#include <string>
#include <functional>

// 加入<sstream>库，否则在另外三个头文件中创建stringstream类的对象时会报错
#include <sstream>


namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	// 将整数值映射到不同类型的事件
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// 将事件分类，方便过滤
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};


// ## 是预处理器中的一个操作符，称为“粘合（token pasting）”操作符。它的作用是将两个标识符（或标识符和文本）连接成一个标识符。

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
		friend class EventDispatcher; // 将 EventDispatcher 类声明为 Event 类的友元类，允许 EventDispatcher 类访问 Event 类的私有成员
	public:
		virtual EventType GetEventType() const = 0; // 纯虚拟函数声明。GetEventType 函数用于获取事件的类型，返回一个 EventType 枚举值。const = 0 表示这是一个纯虚拟函数，需要在派生类中实现
		virtual const char* GetName() const = 0; //  纯虚拟函数声明。用于获取事件的名称，返回一个指向字符数组的指针
		virtual int GetCategoryFlags() const = 0; //纯虚拟函数，用于获取事件的类别标志（category flags），返回一个整数值。
		virtual std::string ToString() const { return GetName(); } //虚拟函数的默认实现。它返回一个表示事件的字符串

		inline bool IsInCategory(EventCategory category)
		{
			// 内联函数，用于检查事件是否属于特定的事件类别。
			// 它接受一个 EventCategory 枚举值作为参数，并使用按位与操作来检查事件的类别标志是否包含指定的类别。
			// 如果包含，返回 true，否则返回 false。
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false; // 用于表示事件是否已经被处理。初始值为 false，表示事件尚未被处理
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			// 通过调用事件处理函数来标记事件对象是否已经被处理
			if (m_Event.GetEventType() == T::GetStaticType()) // 检查传递给 EventDispatcher 的事件对象（m_Event）的类型是否与模板参数 T 的静态类型相匹配
			{
				m_Event.m_Handled = func(*(T*)&m_Event); // 将 m_Event 对象的 m_Handled 成员设置为函数对象 func 的返回值。函数对象 func 应该返回一个布尔值，表示事件是否被处理
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// 输出流运算符
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		// 获取事件的字符串表示，然后将该字符串输出到指定的输出流中
		return os << e.ToString();
	}
}
