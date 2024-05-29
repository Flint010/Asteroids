#pragma once
#include <SFML/Graphics.hpp>
#include "World/World.h"

#include <memory>

class Player;

class Game
{
public:
	Game();

	void run(int min_fps);

private:
	void processEvent();
	void update(sf::Time timeSinceLastUpdate);
	void render();
	
	void initLVLs();
	void initLVL1();
	void initLVL2();
	void initLVL3();
	void gameOver();
	void youWin();



private:
	sf::RenderWindow _window;
	sf::Text _text;
	World _world;
	std::shared_ptr<Player> _player;
	int _lvl_id = 0;	
};

