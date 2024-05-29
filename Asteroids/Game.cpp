#include "Game.h"
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Player.h"
#include "Enemy/Meteor/SmallMeteor.h"
#include "Enemy/Meteor/BigMeteor.h"
#include "Enemy/Meteor/MediumMeteor.h"
#include "Enemy/Saucer/SmallSaucer.h"
#include "Configuration/Configuration.h"

static const int W = 800;
static const int H = 600;


Game::Game() :
	_window(sf::VideoMode(W, H), "SpaceShip", 7U, sf::ContextSettings(0,0,6)), 
	_world((float)W, (float)H), _player(std::make_shared<Player>(&_world))
{	
	Configuration::player = _player.get();
	_text.setFont(Configuration::fonts.get(Configuration::Fonts::Hardpixel));
	_text.setCharacterSize(15);
	
	_player->setPosition(400.f, 300.f);
	_world.add(_player);
}

void Game::run(int min_fps)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / min_fps);


	while (_window.isOpen()) {
		processEvent();

		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		//update(timeSinceLastUpdate);

		render();
	}
}

void Game::processEvent()
{
	sf::Event event;
	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_window.close();
	}
	//_world.processEvent();
	if(_player.get())
		_player->processEvents();
}

void Game::update(sf::Time timeSinceLastUpdate)
{
	if (Configuration::lives > 0) {

		_world.update(timeSinceLastUpdate);

		_text.setString("Score: " + std::to_string(Configuration::score) + "\nLives: " + std::to_string(Configuration::lives));

		if (!_player->isAlive()) {
			std::cout << "Player dead" << std::endl;
			std::cout << "Score: " << Configuration::score << std::endl;
			_player->livenUp();
			_player->setPosition(400.f, 300.f);
			_world.add(_player);
		}
		if (_world.size() == 1) {
			initLVLs();
		}
	}
	else {
		gameOver();
	}
}

void Game::render()
{
	_window.clear();
	_window.draw(_world);
	_window.draw(_text);
	_window.display();
}

void Game::initLVLs()
{
	switch (_lvl_id)
	{
	case 0:
		initLVL1();
		break;
	case 1:
		initLVL2(); 
		break;
	case 2:
		initLVL3();
		break;
	default:
		youWin();
		break;
	}
}

void Game::initLVL1()
{
	auto meteor = std::make_shared<BigMeteor>(&_world);
	meteor->setPosition(0, std::rand() % H);
	_world.add(meteor);

	meteor.reset(new BigMeteor(&_world));
	meteor->setPosition(W, std::rand() % H);
	_world.add(meteor);

	Saucer::newSaucer(&_world);
	_lvl_id++;
}

void Game::initLVL2()
{
	auto meteor = std::make_shared<BigMeteor>(&_world);
	meteor->setPosition(0, std::rand() % H);
	_world.add(meteor);

	meteor.reset(new BigMeteor(&_world));
	meteor->setPosition(W, std::rand() % H);
	_world.add(meteor);

	meteor.reset(new BigMeteor(&_world));
	meteor->setPosition(W, std::rand() % H);
	_world.add(meteor);

	Saucer::newSaucer(&_world);
	_lvl_id++;
}

void Game::initLVL3()
{
	auto meteor = std::make_shared<BigMeteor>(&_world);
	meteor->setPosition(0, std::rand() % H);
	_world.add(meteor);

	meteor.reset(new BigMeteor(&_world));
	meteor->setPosition(W, std::rand() % H);
	_world.add(meteor);

	meteor.reset(new BigMeteor(&_world));
	meteor->setPosition(W, std::rand() % H);
	_world.add(meteor);

	Saucer::newSaucer(&_world);
	Saucer::newSaucer(&_world);
	_lvl_id++;
}

void Game::gameOver()
{
	std::string score("Score: " + std::to_string(Configuration::score));
	std::string game_over("GAME OVER\n\n");
	_text.setString(game_over + score);
	_text.setOrigin((float)_text.getGlobalBounds().getSize().x / 2.f, (float)_text.getGlobalBounds().getSize().y / 2.f);
	_text.setPosition(W / 2.f, H / 2.f);
}

void Game::youWin()
{
	std::string score("Score: " + std::to_string(Configuration::score) + "\nLives: " + std::to_string(Configuration::lives));
	std::string you_win("You win\n\n");
	_text.setString(you_win + score);
	_text.setOrigin((float)_text.getGlobalBounds().getSize().x / 2.f, (float)_text.getGlobalBounds().getSize().y / 2.f);
	_text.setPosition(W / 2.f, H / 2.f);
}


