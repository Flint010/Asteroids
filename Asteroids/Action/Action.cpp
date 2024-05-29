#include "Action.h"

Action::Action(const sf::Keyboard::Key& key, int type): 
	_type(type)
{
	_event.type = type & (int)Type::Pressed ? sf::Event::KeyPressed : sf::Event::KeyReleased;
	_event.key.code = key;	
}

Action::Action(const sf::Mouse::Button& button, int type):
	_type(type)
{
	_event.type = type & (int)Type::Pressed ? sf::Event::MouseButtonPressed : sf::Event::MouseButtonReleased;
	_event.mouseButton.button = button;
}

Action::Action(const Action& act)
{
	memcpy(&_event, &act._event, sizeof(sf::Event));
	_type = act._type;
}

bool Action::test() const // for real time
{
	bool res = false;

	switch (_event.type)
	{
	case sf::Event::KeyPressed:
		res = sf::Keyboard::isKeyPressed(_event.key.code);
		break;
	case sf::Event::MouseButtonPressed:
		res = sf::Mouse::isButtonPressed(_event.mouseButton.button);
		break;
	default:
		break;
	}
	
	return res;	
}

Action& Action::operator=(const Action& act) 
{
	memcpy(&_event, &act._event, sizeof(sf::Event));
	_type = act._type;
	return *this;
}

bool Action::operator==(const sf::Event& event) const
{
	bool res = false;

	switch (event.type)
	{
	case sf::Event::EventType::KeyPressed:
		if (_type & (int)Type::Pressed && _event.type == sf::Event::KeyPressed)
			res = _event.key.code == _event.key.code;
		break;
	case sf::Event::EventType::KeyReleased:
		if (_type & (int)Type::Released && _event.type == sf::Event::KeyReleased)
			res = _event.key.code == _event.key.code;
		break;
	case sf::Event::EventType::MouseButtonPressed:
		if (_type & (int)Type::Pressed && _event.type == sf::Event::MouseButtonPressed)
			res = _event.mouseButton.button == _event.mouseButton.button;
		break;
	case sf::Event::EventType::MouseButtonReleased:
		if (_type & (int)Type::Released && _event.type == sf::Event::MouseButtonReleased)
			res = _event.mouseButton.button == _event.mouseButton.button;
		break;
	default:
		break;
	}

	return res;
}

bool Action::operator==(const Action& action) const
{
	return _type == action._type && action == _event;
}
