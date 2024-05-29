#include "ShootPlayer.h"
#include <corecrt_math_defines.h>
#include <memory>

#include "iostream"

#include "../Configuration/Configuration.h"
#include "../World/World.h"
#include "../Collision.h"

ShootPlayer::ShootPlayer(Player& player): Shoot(Configuration::Texture::ShootPlayer, player.getWorld())
{
	_sprite.setTextureRect(sf::IntRect(145, 964, 10, 23));
	_sprite.setOrigin((float)_sprite.getTextureRect().width/2.f, (float)_sprite.getTextureRect().height/2.f);

	_duration = sf::seconds(1.5);
	float angle = player.getSprite().getRotation() / 180 * (float)M_PI - (float)M_PI / 2;
	_impulse = sf::Vector2f(std::cos(angle), std::sin(angle)) * 500.f;
	setPosition(player.getPosition());
	_sprite.setRotation(player.getSprite().getRotation());
	_world->add(Configuration::Sounds::LaserPlayer);
}

bool ShootPlayer::isCollide(const Entity& entity) const
{
	if (dynamic_cast<const Player*>(&entity) == nullptr) {
		return Collision::circleTest(_sprite, entity.getSprite());
	}
	return false;
}
