#include "Saucer.h"

#include <memory>
#include <random>
#include "../../Collision.h"
#include "../../Configuration/Configuration.h"
#include "../../Shoot/ShootSaucer.h"
#include "../../Shoot/ShootPlayer.h"
#include "../Meteor/Meteor.h"
#include "BigSaucer.h"
#include "SmallSaucer.h"

void Saucer::onDestroy()
{
    Enemy::onDestroy();
    _world->add(Configuration::Sounds::Boom);
}

bool Saucer::isCollide(const Entity& entity) const
{
    if (dynamic_cast<const ShootSaucer*>(&entity) == nullptr && dynamic_cast<const Meteor*>(&entity) == nullptr) {
        return Collision::circleTest(_sprite, entity.getSprite());
    }
    return false;
}

void Saucer::update(sf::Time& dTime)
{
    float seconds = dTime.asSeconds();
    std::shared_ptr<Entity> near = nullptr;
    float near_distance = 300;

    for (auto entity_ptr : _world->getEntities())
    {
        if (entity_ptr.get() != this && (dynamic_cast<const Meteor*>(entity_ptr.get()) || dynamic_cast<const ShootPlayer*>(entity_ptr.get())))
        {
            float x = getPosition().x - entity_ptr->getPosition().x;
            float y = getPosition().y - entity_ptr->getPosition().y;
            float dist = std::sqrt(x * x + y * y);
            if (dist < near_distance) {
                near_distance = dist;
                near = entity_ptr;
            }
        }
    }
    if (near != nullptr)
    {
        sf::Vector2f pos = near->getPosition() - getPosition();
        float angle_rad = std::atan2(pos.y, pos.x);
        _impulse -= sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 300.f * seconds;
    }
    else {
        sf::Vector2f pos = Configuration::player->getPosition() -
            getPosition();
        float angle_rad = std::atan2(pos.y, pos.x);
        _impulse += sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 100.f * seconds;
    }
    if (_impulse.x > 100) _impulse.x = 100;
    if (_impulse.x < -100) _impulse.x = -100;
    if (_impulse.y > 100) _impulse.y = 100;
    if (_impulse.y < -100) _impulse.y = -100;
    _sprite.move(seconds * _impulse);
}

void Saucer::newSaucer(World* world)
{
    std::shared_ptr<Saucer> res = nullptr;

    std::default_random_engine gen;
    std::uniform_real_distribution<float> distribution0(0.f, 1.f);
    std::uniform_real_distribution<float> distribution1(0.f, (float)world->getY());
    float rand1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float rand2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (float)world->getY());


    if (rand1 > Configuration::score/3000.f)
        res = std::make_shared<BigSaucer>(world);
    else
        res = std::make_shared <SmallSaucer>(world);
    
    res->setPosition(distribution0(gen) * world->getX(), rand2);
    world->add(res);
}

