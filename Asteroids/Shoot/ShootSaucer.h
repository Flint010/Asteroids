#pragma once

#include "Shoot.h"

class SmallSaucer;
class ShootSaucer: public Shoot
{
public:
	ShootSaucer(const ShootSaucer&) = delete;
	ShootSaucer& operator=(const ShootSaucer&) = delete;
	explicit ShootSaucer(SmallSaucer& saucer);

	// ������������ ����� Shoot
	bool isCollide(const Entity& entity) const override;
};

