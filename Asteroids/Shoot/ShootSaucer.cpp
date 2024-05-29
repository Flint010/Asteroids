#include "ShootSaucer.h"

#include <corecrt_math_defines.h>

#include <iostream>

#include "../Enemy/Saucer/SmallSaucer.h"
#include "../Configuration/Configuration.h"
#include "../Collision.h"
#include "../Player.h"

ShootSaucer::ShootSaucer(SmallSaucer& saucer): Shoot(Configuration::Texture::ShootSaucer, saucer.getWorld())
{
    _duration = sf::seconds(1);
    sf::Vector2f pos = Configuration::player->getPosition() - saucer.getPosition();

    float accuracy_lost = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.f) - 1.f) * (float)M_PI / ((200 + Configuration::score) / 100.f);

    std::cout << accuracy_lost << std::endl;

    float angle_rad = std::atan2(pos.y, pos.x) + accuracy_lost;
    float angle_deg = angle_rad * 180 / (float)M_PI;

    _impulse = sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 500.f;
    setPosition(saucer.getPosition());
    _sprite.setRotation(angle_deg + 90);
    _world->add(Configuration::Sounds::LaserEnemy);
}

bool ShootSaucer::isCollide(const Entity& entity) const
{ 
    if (dynamic_cast<const Saucer*>(&entity) == nullptr) {
        return Collision::circleTest(_sprite, entity.getSprite());
    }
    return false;
}
