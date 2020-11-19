#include "GameObservers.h"
#include <iostream>

Observer::~Observer(){}

Observer::Observer(){};

Subject::Subject()
{
	_observers = new list<Observer*>;
}

Subject::~Subject()
{
	delete _observers;
}

void Subject::Attach(Observer* o)
{
	_observers->push_back(o);
}

void Subject::Detach(Observer* o)
{
	_observers->remove(o);
}

void Subject::Notify()
{
	list<Observer *>::iterator i = _observers->begin();
	
	for(; i != _observers->end(); ++i)
	{
		(*i)->Update();
	}
}

PhaseObserver::PhaseObserver() {}

PhaseObserver::PhaseObserver(Subject* s)
{
	_subject = s;
	_subject->Attach(this);
}

PhaseObserver::~PhaseObserver()
{
	_subject->Detach(this);
}

void PhaseObserver::Update()
{
	display();
}

void PhaseObserver::display()
{
	//get variables from model
	cout << endl; //add variables
}

StatisticsObserver::StatisticsObserver() {}

StatisticsObserver::StatisticsObserver(Subject* s)
{
	_subject = s;
	_subject->Attach(this);
}

StatisticsObserver::~StatisticsObserver()
{
	_subject->Detach(this);
}

void StatisticsObserver::Update()
{
	display();
}

void StatisticsObserver::display()
{
	//get variables from model
	cout << endl; //add variables
}

