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

void HitboxComponent::update(sf::Vector2f currentPosition, float adjustX, float adjustY)
{
	currentPosition = sf::Vector2f(currentPosition.x + adjustX, currentPosition.y + adjustY);
	this->hitbox.setPosition(currentPosition);
}
