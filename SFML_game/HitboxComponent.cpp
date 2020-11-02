#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(float x, float y, float width, float height)
{
	this->originPoint = sf::Vector2f(x, y);
	this->hitbox.setPosition(originPoint);
	this->hitbox.setSize(sf::Vector2f(width, height));
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

const sf::RectangleShape& HitboxComponent::getHitbox() const
{
	return this->hitbox;
}

void HitboxComponent::update(const float& dt, sf::Vector2f currentPosition)
{
	this->hitbox.setPosition(currentPosition);
}
