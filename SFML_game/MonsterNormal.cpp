#include "MonsterNormal.h"

void MonsterNormal::initComponents()
{
	this->createMovementComponent(this->walkSpeed, 15.f, 5.f);
	this->createAnimationComponent(this->textureSheet);

	// fix later
	this->createHitboxComponent(this->originPoint.x + 45.f, this->originPoint.y + 90.f, 20.f);
	this->adjustParamHitbox = sf::Vector2f(45.f, 90.f);
	this->animationComponent->addAnimation("WALK", 10.f, 0, 0, 9, 0, 377, 404);
}

MonsterNormal::MonsterNormal(float x, float y, Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture& texture_sheet)
	: Monster(x, y, attribute, health, walk_speed, damage, texture_sheet)
{

	this->initComponents();
	
}

MonsterNormal::~MonsterNormal()
{
}
