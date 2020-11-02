#include "Entity.h"

void Entity::initVariables()
{
	this->movementComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}

// Component functions

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(float x, float y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(x, y, width, height);
}

const sf::Vector2f Entity::getPosition() const
{
	return this->sprite.getPosition();
}

HitboxComponent* Entity::getHitboxComponent() const
{
	return this->hitboxComponent;
}

// Functions

void Entity::setPositions(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
	}
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
