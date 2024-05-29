#include "MediumMeteor.h"

#include <memory>

#include "SmallMeteor.h"
#include "../../Configuration/Configuration.h"

MediumMeteor::MediumMeteor(World* world): 
	Meteor((Configuration::Texture)(std::rand() % 3 + (int)Configuration::Texture::MediumMeteor1), world)
{
	_sprite.setOrigin((float)_sprite.getTextureRect().width / 2.f, (float)_sprite.getTextureRect().height / 2.f);

	_impulse *= 50.f;
}

void MediumMeteor::onDestroy()
{
	Meteor::onDestroy();
	for (int i = 0; i < std::rand() % 2 + 2; i++) {
		auto meteor = std::make_shared<SmallMeteor>(_world);
		meteor->setPosition(getPosition());
		_world->add(meteor);
	}
	_world->add(Configuration::Sounds::Explosion1);
}

int MediumMeteor::getPoints() const
{
	return 30;
}
