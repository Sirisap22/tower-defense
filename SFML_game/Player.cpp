#include "Player.h"
// Initializer functions
void Player::initVariables()
{
	this->health = 100;
	this->money = 300;
}

void Player::initComponents()
{
	
}

// Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPositions(x, y);
	
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_RIGHT", 10.f, 0, 0, 19, 0, 333, 314);

}

Player::~Player()
{
}

// Functions
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if (this->movementComponent->idle()) {
		this->animationComponent->play("IDLE_RIGHT", dt);
	}
}
