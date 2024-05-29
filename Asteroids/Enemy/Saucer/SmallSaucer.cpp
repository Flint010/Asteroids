#include "SmallSaucer.h"

#include <memory>

#include "../../Configuration/Configuration.h"
#include "../../Shoot/ShootSaucer.h"

SmallSaucer::SmallSaucer(World* world): Saucer(Configuration::Texture::SmallSaucer, world)
{
    _timeSinceLastShoot = sf::Time::Zero;
    _world->add(Configuration::Sounds::SaucerSpawn2);
    _impulse *= 100.f;
}

void SmallSaucer::update(sf::Time& dTime)
{
    Saucer::update(dTime);
    _timeSinceLastShoot += dTime;
    if (_timeSinceLastShoot > sf::seconds(1.5))
    {
        if (Configuration::player != nullptr)
            _world->add(std::make_shared<ShootSaucer>(*this));
        _timeSinceLastShoot = sf::Time::Zero;
    }
}

int SmallSaucer::getPoints() const
{
    return 200;
}
