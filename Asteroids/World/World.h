#pragma once

#include <list>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>

#include "../Configuration/Configuration.h"

class Entity;

class World : public sf::Drawable
{
public:
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	World(float x, float y);
	~World();
	
	void add(std::shared_ptr<Entity> entity);
	void add(Configuration::Sounds sound_id);

	const std::list<std::shared_ptr<Entity>> getEntities() const;
	int getX() const;
	int getY() const;
	int size() const;

	void clear();
	bool isCollide(const Entity& entity);

	void processEvent();
	void update(sf::Time timeSinceLastUpdate);


private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::list<std::shared_ptr<Entity>> _entities;
	std::list<std::shared_ptr<Entity>> _entities_tmp;

	std::list<std::unique_ptr<sf::Sound>> _sounds;

	const int _x;
	const int _y;
};

