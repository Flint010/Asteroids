#include "Enemy.h"
#include <corecrt_math_defines.h>
#include "../Configuration/Configuration.h"

Enemy::Enemy(Configuration::Texture tex_id, World* world): Entity(tex_id, world)
{
	float angle = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.f * (float)M_PI)));
	_impulse = sf::Vector2f(std::cos(angle), std::sin(angle));
}

void Enemy::onDestroy()
{
	Entity::onDestroy();
	Configuration::score += getPoints();
}
