#pragma once
#include <SFML/Graphics.hpp>
#include <utility>

#include "Entity.h"
#include "Action/ActionTarget.h"

class Player: public Entity, public ActionTarget<int>
{
public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player(World* world);

	void processEvents() override;
	void shoot();
	void goToHyperspace();
	void livenUp();

	void onDestroy() override;
	bool isCollide(const Entity& entity) const override;
	void update(sf::Time& dTime) override;

private:
	bool _isMoving;
	int _rotation;
	sf::Time _timeSinceLastShoot;
	sf::Time _timeSinceLastTeleport;
};

