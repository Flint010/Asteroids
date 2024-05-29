#pragma once
#include <SFML/Graphics.hpp>

template<typename T>
class ActionTarget;

class Action
{
public:	
	enum class Type{
		RealTime = 1,
		Pressed = 1 << 1,
		Released = 1 << 2
	};

	Action(const sf::Keyboard::Key& key, int type = (int)Type::RealTime|(int)Type::Pressed);
	Action(const sf::Mouse::Button& button, int type = (int)Type::RealTime | (int)Type::Pressed);
	Action(const Action& act);


	bool test() const;

	Action& operator=(const Action& act);
	bool operator==(const sf::Event& event) const;
	bool operator==(const Action& action) const;

private:
	friend ActionTarget<int>;

	sf::Event _event;
	int _type;
};


