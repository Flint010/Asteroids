#pragma once

#include "../Entity.h"

class Shoot: public Entity
{
public:
	Shoot(const Shoot&) = delete;
	Shoot& operator=(const Shoot&) = delete;
	using Entity::Entity;

	void update(sf::Time& dTime) override;

protected:
	sf::Time _duration;
};

