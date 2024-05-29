#include "BigMeteor.h"

#include <memory>

#include "../../Configuration/Configuration.h"
#include "MediumMeteor.h"


BigMeteor::BigMeteor(World* world):
	Meteor((Configuration::Texture)(std::rand() % 3 + (int)Configuration::Texture::BigMeteor1), world)
{
	_sprite.setOrigin((float)_sprite.getTextureRect().width / 2.f, (float)_sprite.getTextureRect().height / 2.f);

	_impulse *= 50.f;
}

void BigMeteor::onDestroy()
{
	Meteor::onDestroy();
	for (int i = 0; i < std::rand() % 2 + 2; i++) {
		auto meteor = std::make_shared<MediumMeteor>(_world);
		meteor->setPosition(getPosition());
		_world->add(meteor);
	}
	_world->add(Configuration::Sounds::Explosion1);
}

int BigMeteor::getPoints() const
{
	return 20;
}
