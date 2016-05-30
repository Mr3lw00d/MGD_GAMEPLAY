#include "RegistryEventHandler.h"
#include <stdio.h>
#include "RegistryEventPublisher.h"

class A
{
public:
	A()
	{
		handler.Subscribe(this, &A::F, "A/Event");
	}

	void F()
	{
		printf("A::F()");
	}

private:
	RegistryEventHandler<A> handler;
};

class B
{
public:
	B() 
	{
		sender.SetPath("A/Event");
	}

	void sendEvent()
	{
		sender.Raise();
	}

private:
	RegistryEventPublisher<void> sender;
};

int main()
{
	EventRegistry::CreateInstance();

	A obj1;
	B obj2;
	obj2.sendEvent();

	return 0;
}