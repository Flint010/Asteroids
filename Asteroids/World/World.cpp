#include "World.h"

#include "../Entity.h"
#include "../Player.h"
#include "../Action/ActionTarget.h"
#include <iostream>

World::World(float x, float y) :
	_x(x), _y(y), _entities(0), _entities_tmp(0)
{
}

World::~World()
{
	clear();
}

void World::add(std::shared_ptr<Entity> entity)
{
	_entities_tmp.push_back(entity);
}

void World::add(Configuration::Sounds sound_id)
{
	auto sound = std::make_unique<sf::Sound>(Configuration::sounds.get(sound_id));
	sound->setAttenuation(0);
	sound->play();
	_sounds.push_back(std::move(sound));
}

const std::list<std::shared_ptr<Entity>> World::getEntities() const
{
	return _entities;
}

int World::getX() const
{
	return _x;
}

int World::getY() const
{
	return _y;
}

int World::size() const
{
	return _entities.size() + _entities_tmp.size();
}

void World::clear()
{
	_entities.clear();
	_entities_tmp.clear();
	_sounds.clear();
}

bool World::isCollide(const Entity& entity)
{
	for (auto& x : _entities) {
		if (entity.isCollide(*x))
			return true;
	}
	return false;
}

void World::processEvent()
{
	for (auto& x : _entities) {
		auto ptr = std::dynamic_pointer_cast<ActionTarget<int>>(x);
		if (ptr.get() != nullptr) {
			ptr->processEvents();
		}
	} 
}

void World::update(sf::Time timeSinceLastUpdate)
{
	//std::cout << "_entities.size = " << _entities.size() << std::endl;
	//std::cout << "_entities_tmp.size = " << _entities_tmp.size() << std::endl;

	try
	{
		//_entities.merge(_entities_tmp);
		/*for (auto& x : _entities_tmp) {
			_entities.push_back(x);
		}
		_entities_tmp.clear();*/

		_entities.splice(_entities.end(), _entities_tmp);
	}
	catch (...)
	{
		std::cout << "Error" << std::endl;
	}

	for (auto& x : _entities) {
		x->update(timeSinceLastUpdate);
		bool isChange = false;
		auto pos = x->getPosition();

		if (pos.x < 0) {
			pos.x = _x;
			pos.y = _y - pos.y;
			isChange = true;
		}
		else if (pos.x > _x) {
			pos.x = 0.f;
			pos.y = _y - pos.y;
			isChange = true;
		}
		if (pos.y < 0) {
			pos.y = _y;
			isChange = true;
		}
		else if (pos.y > _y) {
			pos.y = 0;
			isChange = true;
		}
		if (isChange) x->setPosition(pos);
	}
	
	for (auto it_i = _entities.begin(); it_i != _entities.end(); it_i++) {
		auto it_j = it_i;
		it_j++;
		for ( ; it_j != _entities.end(); it_j++) {
			if ((*it_i)->isAlive() && (*it_i)->isCollide(**it_j))
				(*it_i)->onDestroy();
			if ((*it_j)->isAlive() && (*it_j)->isCollide(**it_i))
				(*it_j)->onDestroy();
		}
	}

	for (auto it = _entities.begin(); it != _entities.end();) {
		if (!(*it)->isAlive()) {
			it = _entities.erase(it);
		}
		else
			it++;
	}

	_sounds.remove_if([](const std::unique_ptr<sf::Sound>& ptr)->bool {
			return ptr->getStatus() != sf::Sound::Status::Playing;
		});
}


void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& x : _entities)
		target.draw(*x, states);
}