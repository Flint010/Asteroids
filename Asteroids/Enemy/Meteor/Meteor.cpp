#include "Meteor.h"

#include <memory>
#include "../../Collision.h"

bool Meteor::isCollide(const Entity& entity) const
{
    if (dynamic_cast<const Meteor*>(&entity) == nullptr) {
        return Collision::circleTest(_sprite, entity.getSprite());
    }
    return false;
}

void Meteor::update(sf::Time& dTime)
{
    float seconds = dTime.asSeconds();
    _sprite.move(seconds * _impulse);
}

