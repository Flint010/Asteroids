#pragma once

#include "../Enemy.h"

class Meteor: public Enemy
{
public:
	Meteor(const Meteor&) = delete;
	Meteor& operator=(const Meteor&) = delete;
	using Enemy::Enemy;
	
	bool isCollide(const Entity& entity) const override;
	void update(sf::Time& dTime) override;
};

