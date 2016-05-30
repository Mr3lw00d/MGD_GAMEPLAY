#include "EventRegistry.h"
#include "RegistryEventPublisher.h"
#include "RegistryEventHandler.h"
#include "string.h"

void EventRegistry::CreateInstance()
{
	if(GetSingletonPtr() == NULL)
		new EventRegistry();
}

EventRegistry::EventRegistry()
{
}

EventRegistry::~EventRegistry()
{
}

/*
EVENT HANDLER
*/

EventRegistry::EventHandler::EventHandler()
	: m_pNextHandler(NULL)
{
}

EventRegistry::EventHandler::~EventHandler()
{
	UnsubscribeEventHandler();		
}

void EventRegistry::EventHandler::SetNextHandler( EventHandler* i_pNextHandler )
{
	m_pNextHandler = i_pNextHandler;
}

EventRegistry::EventHandler* EventRegistry::EventHandler::GetNextHandler() const
{
	return m_pNextHandler;
}

void EventRegistry::EventHandler::SubscribeEventHandler(const std::string& i_oEventPath)
{
	EventsMap& vRegistry(EventRegistry::GetSingleton().EditRegistry());
	EventRegistry::EventHandler* pEventHandler = vRegistry[i_oEventPath];
	if (pEventHandler)
	{
		while(pEventHandler->GetNextHandler())
		{
			pEventHandler = pEventHandler->GetNextHandler();
		}

		pEventHandler->SetNextHandler(this);
	}
	else
	{
		vRegistry[i_oEventPath] = this;
	}

	m_oEventPath = i_oEventPath;


}

void EventRegistry::EventHandler::UnsubscribeEventHandler()
{
	EventsMapIt it = EventRegistry::GetSingleton().m_Registry.find(GetPath());
	if (it != EventRegistry::GetSingleton().m_Registry.end())
	{
		EventRegistry::EventHandler* pEventHandler = (*it).second;
		if (pEventHandler)
		{
			if(pEventHandler == this)
			{
				if(this->GetNextHandler())
				{
					pEventHandler = this->GetNextHandler();
				}
				else
				{
					pEventHandler = NULL;
				}
			}
			else
			{
				while(pEventHandler->GetNextHandler() && pEventHandler->GetNextHandler() != this)
				{
					pEventHandler = pEventHandler->GetNextHandler();
				}

				pEventHandler->SetNextHandler(this->GetNextHandler());
			}
		}
	
		if (!pEventHandler)
		{
			EventRegistry::GetSingleton().m_Registry.erase(it);
		}
	}
}