#include "MonsterHeavy.h"

void MonsterHeavy::initComponents()
{
    this->createMovementComponent(this->walkSpeed, 15.f, 5.f);
    this->createAnimationComponent(this->textureSheet);

    this->animationComponent->addAnimation("WALK", 10.f, 0, 0, 9, 0, 445, 469);
}

MonsterHeavy::MonsterHeavy(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture& texture_sheet)
    : Monster(x, y, health, skill, walk_speed, damage, texture_sheet)
{
    this->initComponents();
}

MonsterHeavy::~MonsterHeavy()
{
}
