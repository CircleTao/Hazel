#pragma once

#include "Hazel/Core.h"
// ����һ��ʼ����ʾ�޷��ҵ�Դ�ļ�
// ����Ƶĩβ����ʾ����޸�premake5.lua�����������ļ���

#include <string>
#include <functional>

// ����<sstream>�⣬��������������ͷ�ļ��д���stringstream��Ķ���ʱ�ᱨ��
#include <sstream>


namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	// ������ֵӳ�䵽��ͬ���͵��¼�
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// ���¼����࣬�������
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};


// ## ��Ԥ�������е�һ������������Ϊ��ճ�ϣ�token pasting���������������������ǽ�������ʶ�������ʶ�����ı������ӳ�һ����ʶ����

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
		friend class EventDispatcher; // �� EventDispatcher ������Ϊ Event �����Ԫ�࣬���� EventDispatcher ����� Event ���˽�г�Ա
	public:
		virtual EventType GetEventType() const = 0; // �����⺯��������GetEventType �������ڻ�ȡ�¼������ͣ�����һ�� EventType ö��ֵ��const = 0 ��ʾ����һ�������⺯������Ҫ����������ʵ��
		virtual const char* GetName() const = 0; //  �����⺯�����������ڻ�ȡ�¼������ƣ�����һ��ָ���ַ������ָ��
		virtual int GetCategoryFlags() const = 0; //�����⺯�������ڻ�ȡ�¼�������־��category flags��������һ������ֵ��
		virtual std::string ToString() const { return GetName(); } //���⺯����Ĭ��ʵ�֡�������һ����ʾ�¼����ַ���

		inline bool IsInCategory(EventCategory category)
		{
			// �������������ڼ���¼��Ƿ������ض����¼����
			// ������һ�� EventCategory ö��ֵ��Ϊ��������ʹ�ð�λ�����������¼�������־�Ƿ����ָ�������
			// ������������� true�����򷵻� false��
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false; // ���ڱ�ʾ�¼��Ƿ��Ѿ���������ʼֵΪ false����ʾ�¼���δ������
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
			// ͨ�������¼�������������¼������Ƿ��Ѿ�������
			if (m_Event.GetEventType() == T::GetStaticType()) // ��鴫�ݸ� EventDispatcher ���¼�����m_Event���������Ƿ���ģ����� T �ľ�̬������ƥ��
			{
				m_Event.m_Handled = func(*(T*)&m_Event); // �� m_Event ����� m_Handled ��Ա����Ϊ�������� func �ķ���ֵ���������� func Ӧ�÷���һ������ֵ����ʾ�¼��Ƿ񱻴���
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// ����������
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		// ��ȡ�¼����ַ�����ʾ��Ȼ�󽫸��ַ��������ָ�����������
		return os << e.ToString();
	}
}
