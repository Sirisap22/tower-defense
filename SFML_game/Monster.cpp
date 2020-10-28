#include "Monster.h"

void Monster::initVariables(int health, std::string skill, float walk_speed, int damage)
{
	this->health = health;
	this->skill = skill;
	this->walkSpeed = walk_speed;
	this->damage = damage;
}

Monster::Monster(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture& texture_sheet)
{
	this->initVariables(health, skill, walk_speed, damage);

	this->setPositions(x, y);

	this->initComponents(texture_sheet);

	this->sprite.setScale(-0.5f, 0.5f);
}

Monster::~Monster()
{
}

void Monster::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->animationComponent->play("WALK", dt);
}
