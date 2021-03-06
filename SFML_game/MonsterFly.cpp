#include "MonsterFly.h"

void MonsterFly::initComponents()
{
    this->createMovementComponent(this->walkSpeed, 15.f, 5.f);
    this->createAnimationComponent(this->textureSheet);

    // fix later
    this->createHitboxComponent(this->originPoint.x + 55.f, this->originPoint.y + 35.f, 20.f);
    this->adjustParamHitbox = sf::Vector2f(55.f, 35.f);

    this->animationComponent->addAnimation("WALK", 10.f, 0, 0, 9, 0, 344, 290);
}

MonsterFly::MonsterFly(float x, float y, Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture& texture_sheet)
    : Monster(x, y, attribute, health, walk_speed, damage, texture_sheet)
{
    this->initComponents();
}

MonsterFly::~MonsterFly()
{
}
