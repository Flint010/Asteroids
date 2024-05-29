#include <iostream>
#include "Game.h"
#include "Configuration/Configuration.h"

int main() {	
	Configuration::initialize();

	Game game;
	game.run(60);

	return 0;
}