#include "Player.h"
#include <corecrt_math_defines.h>

#include <memory>
#include "Configuration/Configuration.h"
#include "Shoot/ShootPlayer.h"
#include "Collision.h"
#include "World/World.h"

Player::Player(World* world) : Entity(Configuration::Texture::Player, world),
	ActionTarget(Configuration::actionMap),
	_isMoving(false), _rotation(0)
{
	_sprite.setPosition({100,100});
	_sprite.setTextureRect(sf::IntRect(30, 930, 40, 37));
	_sprite.setOrigin((float)_sprite.getTextureRect().width / 2.f, (float)_sprite.getTextureRect().height / 2.f);

	bind((int)Configuration::PlayerInputs::Up, [this](const sf::Event&) { _isMoving = true; });
	//bind((int)Configuration::PlayerInputs::UpRelease, [this](const sf::Event&) { _isMoving = false; });
	bind((int)Configuration::PlayerInputs::Left, [this](const sf::Event&) { _rotation--; });
	bind((int)Configuration::PlayerInputs::Right, [this](const sf::Event&) { _rotation++; });
	bind((int)Configuration::PlayerInputs::Shoot, [this](const sf::Event&) { shoot(); });
	bind((int)Configuration::PlayerInputs::goHyperspace, [this](const sf::Event&) { goToHyperspace(); });
}

void Player::onDestroy()
{
	Entity::onDestroy();
	Configuration::lives--;
	_world->add(Configuration::Sounds::Boom);
}

bool Player::isCollide(const Entity& entity) const
{
	if (dynamic_cast<const ShootPlayer*>(&entity) == nullptr) {
		return Collision::circleTest(_sprite, entity.getSprite()); 
	}
		return false;
}

void Player::update(sf::Time& dTime)
{
	float seconds = dTime.asSeconds();
	_timeSinceLastShoot += dTime;
	_timeSinceLastTeleport += dTime;

	if (_rotation != 0)
	{
		float angle = _rotation * 250.f * seconds;
		_sprite.rotate(angle);
	}

	if (_isMoving)
	{
		float angle = _sprite.getRotation() / 180.f * (float)M_PI - (float)M_PI / 2.f; // to rad
		_impulse += sf::Vector2f(std::cos(angle), std::sin(angle)) * 300.f * seconds;
	}
	if (_impulse.x > 130) _impulse.x = 130;
	if (_impulse.x < -130) _impulse.x = -130;
	if (_impulse.y > 130) _impulse.y = 130;
	if (_impulse.y < -130) _impulse.y = -130;

	_sprite.move(seconds * _impulse);
}

void Player::processEvents()
{
	_isMoving = 0;
	_rotation = 0;
	ActionTarget::processEvents();
}

void Player::shoot()
{
	if (_timeSinceLastShoot > sf::seconds(0.3f)) {
		_world->add(std::make_shared<ShootPlayer>(*this));
		_timeSinceLastShoot = sf::Time::Zero;
	}
}

void Player::goToHyperspace()
{
	if (_timeSinceLastTeleport > sf::seconds(1.f)) {
		_impulse = sf::Vector2f(0.f, 0.f);
		setPosition(std::rand() % _world->getX(), std::rand() % _world->getY());
		_world->add(Configuration::Sounds::Jump);
		_timeSinceLastTeleport = sf::Time::Zero;
	}
}

void Player::livenUp()
{
	_alive = true;
}
