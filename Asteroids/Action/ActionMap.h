#pragma once

#include <unordered_map>
#include "Action.h"

template<typename T = int>
class ActionMap
{
public:
	ActionMap() = default;

	void map(const T& key, const Action& action);
	const Action& get(const T& key) const;


private:
	std::unordered_map<T, Action> _map;
};

template<typename T>
inline void ActionMap<T>::map(const T& key, const Action& action)
{
	_map.insert({key, action });
}

template<typename T>
inline const Action& ActionMap<T>::get(const T& key) const
{
	return _map.at(key);	
}
