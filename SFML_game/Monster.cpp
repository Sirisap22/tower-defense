#include "Monster.h"

void Monster::initVariables(Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture texture_sheet)
{
	this->health = health;
	this->walkSpeed = walk_speed;
	this->damage = damage;
	this->textureSheet = texture_sheet;
	this->attribute = attribute;

}

Monster::Monster(float x, float y, Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture texture_sheet)
{
	this->initVariables(attribute, health, walk_speed, damage, texture_sheet);

	this->originPoint = sf::Vector2f(x, y);
	//this->sprite.setScale(-0.5f, 0.5f);

	this->setPositions(x, y);

}

Monster::~Monster()
{
}

void Monster::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->animationComponent->play("WALK", dt);

	//this->hitboxComponent->update(dt, this->sprite.getPosition());
}
