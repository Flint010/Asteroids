#pragma once

#include "Saucer.h"

class BigSaucer: public Saucer
{
public:
	BigSaucer(World* world);

	int getPoints() const override;

private:
	sf::Time _timeSinceLastShoot;
};

