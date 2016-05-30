#pragma once
/*
	http://scottbilas.com/publications/gem-singleton/
*/

template <typename T> class Singleton
{
	static T* ms_singleton;

public:
	Singleton()
	{
		ms_singleton = static_cast <T*> (this);
	}

	~Singleton()
	{ 
		ms_singleton = 0; 
	}

	static T& GetSingleton()
	{ 
		return *ms_singleton; 
	}

	static T* GetSingletonPtr()
	{ 
		return ms_singleton; 
	}

	static void Release()
	{
		delete(ms_singleton);
		ms_singleton= NULL;
	}

};

template <typename T> T* Singleton <T>::ms_singleton = 0;
