#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <vector>
enum SoundEffect
{
	w,
	t,
	f,
};

class Observer
{
public:
	virtual ~Observer() {};
	virtual void notify(SoundEffect t_soundEffect)=0;

private:

};

struct Listener
{
	static void notify(SoundEffect
		t_soundEffect)
	{
		for (auto& observer : Listener::m_observers)
		{
			observer->notify(t_soundEffect);
		}
	}
	static std::vector<Observer*>m_observers;
};
class Subject
{
public:
	virtual void notify(SoundEffect t_soundEffect)
	{
		for (auto& observer : Listener::m_observers)
		{
			observer->notify(t_soundEffect);
		}
	}
	void addObserver(Observer * t_observer)
	{
		Listener::m_observers.emplace_back(t_observer);
	}
	void removeObserver(Observer* t_observer)
	{
		Listener::m_observers.erase(
			std::remove(Listener::m_observers.begin(),
				Listener::m_observers.end(),
				t_observer),
			Listener::m_observers.end()
			);
	}
};
#endif // !OBSERVER_H
