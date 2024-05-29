#include "Shoot.h"


void Shoot::update(sf::Time& dTime)
{
	float seconds = dTime.asSeconds();
	_sprite.move(seconds * _impulse);
	_duration -= dTime;
	if (_duration < sf::Time::Zero)
		_alive = false;
}
