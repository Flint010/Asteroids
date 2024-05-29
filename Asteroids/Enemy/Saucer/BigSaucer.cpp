#include "BigSaucer.h"

#include "../../Configuration/Configuration.h"

BigSaucer::BigSaucer(World* world): Saucer(Configuration::Texture::BigSaucer, world)
{
    _world->add(Configuration::Sounds::SaucerSpawn2);
    _impulse *= 400.f;
}

int BigSaucer::getPoints() const
{
    return 100;
}
