#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include "ResourceManager.h"
#include "../Action/ActionMap.h"
#include <memory>

class Player;

class Configuration
{
public:
	Configuration() = delete;
	Configuration(const Configuration&) = delete;
	const Configuration& operator=(const Configuration&) = delete;

	enum class Texture { 
		Player, ShootPlayer, ShootSaucer, SmallSaucer, BigSaucer, 
		BigMeteor1, BigMeteor2, BigMeteor3,
		MediumMeteor1, MediumMeteor2, MediumMeteor3,
		SmallMeteor1, SmallMeteor2, SmallMeteor3
	};
	static ResourceManager<sf::Texture, int> textures;

	enum class PlayerInputs { Up, UpRelease, Left, Right, Shoot, goHyperspace};
	static ActionMap<int> actionMap;

	enum Sounds { Boom, Jump, LaserPlayer, Explosion1, LaserEnemy, SaucerSpawn2 };
	static ResourceManager<sf::SoundBuffer, int> sounds;

	enum Fonts { Hardpixel };
	static ResourceManager<sf::Font, int> fonts;

	static Player *player;
	static uint8_t lives;
	static int score;

	static void initialize();

private:
	static void initTextures();
	static void initPlayerInputs();
	static void initSounds();			
	static void initFonts();			
};

