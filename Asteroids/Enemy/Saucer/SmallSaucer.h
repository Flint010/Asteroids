#pragma once

#include "Saucer.h"

class World;
class SmallSaucer: public Saucer
{
public:
	SmallSaucer(World* world);

	void update(sf::Time& dTime) override;
	int getPoints() const override;

private:
	sf::Time _timeSinceLastShoot;
};

