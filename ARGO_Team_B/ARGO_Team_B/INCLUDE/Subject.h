#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <vector>

class Subject
{
public:
	virtual void registerObserver(Observer* t_obs) {}
	virtual void removeObserver(Observer* t_obs) {};
	virtual void notifyObserver() {};

protected:
	std::vector<Observer*>m_observers;
};
#endif // !SUBJECT_H
