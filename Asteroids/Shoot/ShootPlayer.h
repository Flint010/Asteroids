#pragma once

#include "Shoot.h"
#include "../Player.h"

class ShootPlayer : public Shoot
{
public:
	ShootPlayer(const ShootPlayer&) = delete;
	ShootPlayer& operator=(const ShootPlayer&) = delete;
	explicit ShootPlayer(Player& player);

	// Унаследовано через Shoot
	bool isCollide(const Entity& entity) const override;
};

