#include "Monster.h"

void Monster::initVariables(int health, std::string skill, float walk_speed, int damage, sf::Texture texture_sheet)
{
	this->health = health;
	this->skill = skill;
	this->walkSpeed = walk_speed;
	this->damage = damage;
	this->textureSheet = texture_sheet;

}

Monster::Monster(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture texture_sheet)
{
	this->initVariables(health, skill, walk_speed, damage, texture_sheet);

	this->setPositions(x, y);

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
