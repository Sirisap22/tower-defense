#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(float x, float y, float radius)
{
	this->originPoint = sf::Vector2f(x, y);
	this->hitbox.setPosition(originPoint);
	this->hitbox.setRadius(radius);
	this->hitbox.setOutlineColor(sf::Color::Green);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setFillColor(sf::Color::Transparent);
}

HitboxComponent::~HitboxComponent()
{
}

const sf::Vector2f& HitboxComponent::getOriginPoint() const
{
	return this->originPoint;
}

const sf::CircleShape& HitboxComponent::getHitbox() const
{
	return this->hitbox;
}

void HitboxComponent::update(const float& dt, sf::Vector2f currentPosition, float adjust_parameter)
{
	currentPosition = sf::Vector2f(currentPosition.x + adjust_parameter, currentPosition.y + adjust_parameter);
	this->hitbox.setPosition(currentPosition);
}
