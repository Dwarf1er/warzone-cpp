#pragma once
#include <list>
using namespace std;
class GameEngine;

// Observer Class 
class Observer
{
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

//Subject Class 
class Subject
{
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	virtual ~Subject();
private:
	list<Observer*>* _observers;
};

class PhaseObserver : public Observer
{
public:
	PhaseObserver();
	PhaseObserver(GameEngine* s); //parameter: Model Pointer
	~PhaseObserver();
	void Update();
	void display();
private:
	GameEngine* _subject; //Model Pointer
};

class StatisticsObserver : public Observer
{
public:
	StatisticsObserver();
	StatisticsObserver(GameEngine* s); //parameter: Model Pointer
	~StatisticsObserver();
	void Update() override;
	void display();
private:
	GameEngine* _subject; //Model Pointer
};
