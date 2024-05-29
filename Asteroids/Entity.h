#pragma once

#include <SFML/Graphics.hpp>
#include <utility>

#include "Configuration/Configuration.h"

class World;

class Entity: public sf::Drawable
{
public:
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	Entity(Configuration::Texture text_id, World* world);
	virtual ~Entity() = default;

	virtual void onDestroy();

	template<typename ... Args>
	void setPosition(Args&& ... args) {
		_sprite.setPosition(std::forward<Args>(args) ...);
	}
	const sf::Vector2f& getPosition() const;

	const sf::Sprite& getSprite() const;
	World* getWorld();

	virtual bool isCollide(const Entity& entity) const = 0;
	virtual bool isAlive() const;

	virtual void update(sf::Time& dTime) = 0;

protected:
	sf::Sprite _sprite;
	World* _world;

	sf::Vector2f _impulse;
	bool _alive;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

