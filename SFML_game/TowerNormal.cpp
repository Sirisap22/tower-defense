#include "TowerNormal.h"

TowerNormal::TowerNormal(float x, float y, Entity::EntityAttributes attribute, int damage, int attack_speed, sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3)
	:Tower(x, y, attribute, damage, attack_speed, level_1, level_2, level_3)
{
	this->radius = 300.f;

	this->radiusShape.setRadius(this->radius);
	this->radiusShape.setOutlineColor(sf::Color::Green);
	this->radiusShape.setOutlineThickness(1.f);
	this->radiusShape.setFillColor(sf::Color::Transparent);
	this->radiusShape.setPosition(x - this->radius - 10.f, y - this->radius);
}

TowerNormal::~TowerNormal()
{
}
