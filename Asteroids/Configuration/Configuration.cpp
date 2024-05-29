#include "Configuration.h"

ResourceManager<sf::Texture, int> Configuration::textures;
ActionMap<int> Configuration::actionMap;
ResourceManager<sf::SoundBuffer, int> Configuration::sounds;
ResourceManager<sf::Font, int> Configuration::fonts;
uint8_t Configuration::lives;
int Configuration::score;
Player* Configuration::player = nullptr;

void Configuration::initialize()
{
	srand(time(NULL));
	score = 0;
	lives = 3;
	initTextures();
	initPlayerInputs();
	initSounds();
	initFonts();
}

void Configuration::initTextures()
{
	textures.load((int)Configuration::Texture::Player, "media/Player/ships.png");
	textures.load((int)Configuration::Texture::ShootPlayer, "media/Player/ships.png");
	textures.load((int)Configuration::Texture::BigMeteor1, "media/Meteor/BigMeteor1.png");
	textures.load((int)Configuration::Texture::BigMeteor2, "media/Meteor/BigMeteor2.png");
	textures.load((int)Configuration::Texture::BigMeteor3, "media/Meteor/BigMeteor3.png");
	textures.load((int)Configuration::Texture::MediumMeteor1, "media/Meteor/MediumMeteor1.png");
	textures.load((int)Configuration::Texture::MediumMeteor2, "media/Meteor/MediumMeteor2.png");
	textures.load((int)Configuration::Texture::MediumMeteor3, "media/Meteor/MediumMeteor3.png");
	textures.load((int)Configuration::Texture::SmallMeteor1, "media/Meteor/SmallMeteor1.png");
	textures.load((int)Configuration::Texture::SmallMeteor2, "media/Meteor/SmallMeteor2.png");
	textures.load((int)Configuration::Texture::SmallMeteor3, "media/Meteor/SmallMeteor3.png");
	textures.load((int)Configuration::Texture::SmallSaucer, "media/Saucer/Saucer.png");
	textures.load((int)Configuration::Texture::BigSaucer, "media/Saucer/Saucer.png");
	textures.load((int)Configuration::Texture::ShootSaucer, "media/Saucer/SaucerShoot.png");
}

void Configuration::initPlayerInputs()
{
	actionMap.map((int)PlayerInputs::Up, sf::Keyboard::Up);
	actionMap.map((int)PlayerInputs::UpRelease, Action(sf::Keyboard::Up, (int)Action::Type::Released | (int)Action::Type::RealTime));
	actionMap.map((int)PlayerInputs::Left, sf::Keyboard::Left);
	actionMap.map((int)PlayerInputs::Right, sf::Keyboard::Right);
	actionMap.map((int)PlayerInputs::Shoot, sf::Keyboard::Space);
	actionMap.map((int)PlayerInputs::goHyperspace, sf::Keyboard::LControl);
}

void Configuration::initSounds()
{
	sounds.load(Sounds::Boom, "media/Sounds/boom.wav");
	sounds.load(Sounds::Jump, "media/Sounds/jump.wav");
	sounds.load(Sounds::LaserPlayer, "media/Sounds/laser.wav");
	sounds.load(Sounds::Explosion1, "media/Sounds/boom.wav");
	sounds.load(Sounds::LaserEnemy, "media/Sounds/laser.wav");
	sounds.load(Sounds::SaucerSpawn2, "media/Sounds/jump.wav");
}

void Configuration::initFonts()
{
	fonts.load(Fonts::Hardpixel, "media/Fonts/Hardpixel.ttf");
}