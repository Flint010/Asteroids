#include "Entity.h"

#include "World/World.h"

Entity::Entity(Configuration::Texture text_id, World* world):
	_world(world), _alive(true)
{
	sf::Texture& texture = Configuration::textures.get((int)text_id);
	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x/2.f, texture.getSize().y / 2.f);	
}

void Entity::onDestroy()
{
	_alive = false;
}

const sf::Vector2f& Entity::getPosition() const
{
	return _sprite.getPosition();
}

const sf::Sprite& Entity::getSprite() const
{
	return _sprite;
}

World* Entity::getWorld()
{
	return _world;
}

bool Entity::isAlive() const
{
	return _alive;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}