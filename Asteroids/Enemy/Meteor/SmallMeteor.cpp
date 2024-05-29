#include "SmallMeteor.h"

SmallMeteor::SmallMeteor(World* world): 
	Meteor((Configuration::Texture)(std::rand() % 3 + (int)Configuration::Texture::SmallMeteor1), world)
{
	_sprite.setOrigin(_sprite.getTextureRect().width / 2.f, _sprite.getTextureRect().height / 2.f);

	_impulse *= -100.f;
}

void SmallMeteor::onDestroy()
{
	Meteor::onDestroy();
	_world->add(Configuration::Sounds::Explosion1);
}

int SmallMeteor::getPoints() const
{
	return 40;
}
