#pragma once

#include "../Enemy.h"

class World;

class Saucer: public Enemy
{
public:
	Saucer(const Saucer&) = delete;
	Saucer& operator=(const Saucer&) = delete;
	using Enemy::Enemy;

	virtual void onDestroy();

	bool isCollide(const Entity& entity) const override;
	void update(sf::Time& dTime) override;
	
	static void newSaucer(World* world);
};

