#include "MonsterHeavy.h"

void MonsterHeavy::initComponents()
{
    this->createMovementComponent(this->walkSpeed, 15.f, 5.f);
    this->createAnimationComponent(this->textureSheet);

    // fix later
    this->createHitboxComponent(this->originPoint.x + 100.f-55.f, this->originPoint.y + 120.f, 20.f);
	this->adjustParamHitbox = sf::Vector2f(100.f-55.f, 120.f);


    this->animationComponent->addAnimation("WALK", 10.f, 0, 0, 9, 0, 445, 469);
}

MonsterHeavy::MonsterHeavy(float x, float y, Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture& texture_sheet)
    : Monster(x, y, attribute, health, walk_speed, damage, texture_sheet)
{
    //this->originPoint = sf::Vector2f(x, y);
    //std::cout << "##################### " << this->originPoint.x << " " << this->originPoint.y << " " << this->sprite.getTextureRect().width;
    this->initComponents();
}

MonsterHeavy::~MonsterHeavy()
{
}
