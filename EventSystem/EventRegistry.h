
#pragma once
#include "Singleton.h"
#include <string>
#include <map>

class EventRegistry : public Singleton<EventRegistry>
{
public:
	class EventHandler
	{
	public:
		EventHandler();
		virtual ~EventHandler();

		const std::string& GetPath() const
		{
			return m_oEventPath;
		}

		void SetNextHandler(EventHandler* i_pNextNode);
		EventHandler* GetNextHandler() const;

		void SubscribeEventHandler(const std::string& i_oEventPath);
		void UnsubscribeEventHandler();

		void AddHandler( EventHandler* i_pEventHandler );
		void RemoveHandler(EventHandler* i_pEventHandler);

		virtual void Invoke(const std::string& pParamType, void* i_pParam) = 0;

	private:
		EventHandler*	m_pNextHandler;
		std::string			m_oEventPath;
	};

private:
	typedef std::map<std::string,EventHandler*>		EventsMap;
	typedef EventsMap::iterator						EventsMapIt;

public:
	~EventRegistry();

	static void CreateInstance();	

	const EventsMap& GetRegistry() const
	{
		return m_Registry;
	}

	EventsMap& EditRegistry()
	{
		return m_Registry;
	}

private:
	EventRegistry();

	EventsMap m_Registry;
};