#include "Entity.h"

Entity::Entity()
{
	this->shape.setSize(sf::Vector2f(75.f, 75.f));
	//this->texture.loadFromFile("public/player/idle/1.png");
	//this->shape.setTexture(&texture);
	this->movementSpeed = 100.F;
}

Entity::~Entity()
{
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	this->shape.move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
