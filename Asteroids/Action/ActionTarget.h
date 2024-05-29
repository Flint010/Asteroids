#pragma once

#include <list>
#include <utility>
#include <functional>

#include "ActionMap.h"
#include "Action.h"

template<typename T = int>
class ActionTarget
{
public:
	using FuncType = std::function<void(const sf::Event&)>;

	explicit ActionTarget(const ActionMap<T>& map);

	bool processEvent(const sf::Event& event) const;
	virtual void processEvents();

	void bind(const T& key, const FuncType& callback);
	void unbind(const T& key);

private:
	std::list<std::pair<T, FuncType>> _eventsRealTime;
	std::list<std::pair<T, FuncType>> _eventsPoll;
	const ActionMap<T>& _map;
};

template<typename T>
inline ActionTarget<T>::ActionTarget(const ActionMap<T>& map):
	_map(map)
{
}

template<typename T>
bool ActionTarget<T>::processEvent(const sf::Event& event) const
{
	// TODO: add try this block
	bool res = false;
	for (const auto& action : _eventsPoll) {
		if (_map.get(action.first) == event) {
			action.second(event);
			res = true;
			break;
		}
	}
	return true;
}

template<typename T>
void ActionTarget<T>::processEvents() 
{
	for (const auto& action : _eventsRealTime) {
		if (_map.get(action.first).test())
			action.second(_map.get(action.first)._event);
	}
}

template<typename T>
void ActionTarget<T>::bind(const T& key, const FuncType& callback)
{
	if (_map.get(key)._type & (int)Action::Type::RealTime)
		_eventsRealTime.emplace_back(key, callback);
	else
		_eventsPoll.emplace_back(key, callback);
}

template<typename T>
void ActionTarget<T>::unbind(const T& key)
{
	auto removeFunc = [&key](const std::pair<T, FuncType>& el)->bool
		{
			return key == el.first;
		};

	if (_map.get(key)._type & (int)Action::Type::RealTime)
		_eventsRealTime.remove_if(removeFunc);
	else
		_eventsPoll.remove_if(removeFunc);
}
