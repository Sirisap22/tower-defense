#include "MonsterFly.h"

void MonsterFly::initVariables(int health, std::string skill, float walk_speed, int damage)
{
	this->health = health;
	this->skill = skill;
	this->walkSpeed = walk_speed;
	this->damage = damage;
}

MonsterFly::MonsterFly(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture& texture_sheet)
{
	this->initVariables(health, skill, walk_speed, damage);

	this->setPositions(x, y);

	this->createMovementComponent(this->walkSpeed, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("WALK", 10.f, 0, 0, 9, 0, 344, 290);

	this->sprite.setScale(-0.5f, 0.5f);
}

MonsterFly::~MonsterFly()
{
}

void MonsterFly::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->animationComponent->play("WALK", dt);
}
