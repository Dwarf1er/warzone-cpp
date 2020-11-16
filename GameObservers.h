#pragma once
#include <list>
using namespace std;

class Observer
{
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

class Subject
{
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	~Subject();
private:
	list<Observer*>* _observers;
};

class PhaseObserver : Observer
{
public:
	PhaseObserver();
	PhaseObserver(Subject* s); //parameter: Model Pointer
	~PhaseObserver();
	void Update() override;
	void display();
private:
	Subject* _subject; //Model Pointer
};

class StatisticsObserver : Observer
{
public:
	StatisticsObserver();
	StatisticsObserver(Subject* s); //parameter: Model Pointer
	~StatisticsObserver();
	void Update() override;
	void display();
private:
	Subject* _subject; //Model Pointer
};
