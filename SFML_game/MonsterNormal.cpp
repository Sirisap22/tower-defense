#include "MonsterNormal.h"

void MonsterNormal::initVariables(int health)
{
	this->health = health;
}

MonsterNormal::MonsterNormal(float x, float y, int health, sf::Texture& texture_sheet)
{
	this->initVariables(health);

	this->setPositions(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("WALK", 10.f, 0, 0, 10, 0, 333, 314);
}

MonsterNormal::~MonsterNormal()
{
}

void MonsterNormal::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->animationComponent->play("WALK", dt);
}
