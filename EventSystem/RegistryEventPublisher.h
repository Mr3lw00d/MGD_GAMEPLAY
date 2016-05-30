/*
*	This is the class that is used to register a function to be notified when the event occurs
*/


#pragma once

#include "EventRegistry.h"

template < typename T >
class RegistryEventPublisher
{
public:
	RegistryEventPublisher()
	{
	}
	
	virtual ~RegistryEventPublisher()
	{
	}

	void SetPath(const std::string& i_oEventPath)
	{
		m_oEventPath = i_oEventPath;
	}

	const std::string& GetPath() const
	{
		return m_oEventPath;
	}

	void Raise(const T& i_pParam)
	{
		MGDMap<std::string, EventRegistry::EventHandler*>::iterator it = EventRegistry::GetSingleton().EditRegistry().find(GetPath());
		if (it != EventRegistry::GetSingleton().GetRegistry().end())
		{
			EventRegistry::EventHandler* pNode = (*it).second;
			while (pNode)
			{
				pNode->Invoke(T::ID, static_cast<void*>(&const_cast<T&>(i_pParam)));
				pNode = pNode->GetNextHandler();
			}
		}
		else
		{
			MGD_ASSERT(0);
		}
	}

private:
	std::string	m_oEventPath;
};

template<>
class RegistryEventPublisher<void>
{
public:
	RegistryEventPublisher()		
	{
	}

	virtual ~RegistryEventPublisher()
	{
	}

	void SetPath(const std::string& i_oEventPath)
	{
		m_oEventPath = i_oEventPath;
	}

	const std::string& GetPath() const
	{
		return m_oEventPath;
	}


	void Raise()
	{
		std::map<std::string,EventRegistry::EventHandler*>::const_iterator it =  EventRegistry::GetSingleton().GetRegistry().find(GetPath());
		if(it != EventRegistry::GetSingleton().GetRegistry().end())
		{
			EventRegistry::EventHandler* pNode = (*it).second;
			while (pNode)
			{
				pNode->Invoke("", NULL);
				pNode = pNode->GetNextHandler();
			}
		}
	}

private:
	std::string	m_oEventPath;
};

template<>
class RegistryEventPublisher<const char*>
{
public:
	RegistryEventPublisher()		
	{
	}

	virtual ~RegistryEventPublisher()
	{
	}

	void SetPath(const std::string& i_oEventPath)
	{
		m_oEventPath = i_oEventPath;
	}

	const std::string& GetPath() const
	{
		return m_oEventPath;
	}

	void Raise(const char* i_pParam)
	{
		std::map<std::string,EventRegistry::EventHandler*>::const_iterator it =  EventRegistry::GetSingleton().GetRegistry().find(GetPath());
		if(it != EventRegistry::GetSingleton().GetRegistry().end())
		{
			EventRegistry::EventHandler* pNode = (*it).second;
			while (pNode)
			{
				pNode->Invoke(std::string("const char*"), static_cast<void*>(const_cast<char*>(i_pParam)));
				pNode = pNode->GetNextHandler();
			}
		}
	}

private:
	std::string	m_oEventPath;
};


//IDC
template < typename T >
class AuctionRegistryEventPublisher
{



public:
	AuctionRegistryEventPublisher()
	{
	}

	virtual ~AuctionRegistryEventPublisher()
	{
	}

	void SetPath(const std::string& i_oEventPath)
	{
		m_oEventPath = i_oEventPath;
	}

	const std::string& GetPath() const
	{
		return m_oEventPath;
	}

	void Raise(const T& i_pParam)
	{
		/*was MDGmap*/		std::map<std::string, EventRegistry::EventHandler*>::iterator it = EventRegistry::GetSingleton().EditRegistry().find(GetPath());
		if (it != EventRegistry::GetSingleton().GetRegistry().end())
		{
			EventRegistry::EventHandler* pNode = (*it).second;
			while (pNode)
			{
				pNode->Invoke(T::ID, static_cast<void*>(&const_cast<T&>(i_pParam)));
				pNode = pNode->GetNextHandler();
			}
		}
		else
		{
			//MGD_ASSERT(0); //IDC commented
		}
	}

private:
	std::string	m_oEventPath;
};





