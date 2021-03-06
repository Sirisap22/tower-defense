#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
	this->movementState = MovementState::IDLE;
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}



// Functions
const MovementComponent::MovementState MovementComponent::getMovementState() const
{
	return this->movementState;
}

void MovementComponent::setMovementState(MovementState state)
{
	this->movementState = state;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float dt)
{
	/* Accelerating a sprite until it reaches the max velocity. */

	this->velocity.x += this->acceleration * dir_x;	
	this->velocity.y += this->acceleration * dir_y;
}



void MovementComponent::update(const float& dt)
{
	/* Decelerates the sprite and controls the maximum velocity. Moves the sprite.*/

	if (this->velocity.x > 0.f) // Check for positive x
	{
		// Change movement state
		this->movementState = MovementState::RIGHT;

		// Max velocity check x positive
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		// Deceleration x positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) // Check for negative x
	{
		this->movementState = MovementState::LEFT;
		// Max velocity check x negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		// Deceleration x negative
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) // Check for positive y
	{
		// Max velocity check y positive
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		// Deceleration y positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) // Check for negative y
	{
		// Max velocity check y negative
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		// Deceleration y negative
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	// Final move
	this->sprite.move(this->velocity * dt); // Uses velocity
}
