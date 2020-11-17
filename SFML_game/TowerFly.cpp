#include "TowerFly.h"

TowerFly::TowerFly(float x, float y, Entity::EntityAttributes attribute, int damage, int attack_speed, std::map<std::string, sf::Texture> textures)
	:Tower(x, y, attribute, damage, attack_speed, textures)
{
	this->radius = 500.f;

	this->radiusShape.setRadius(this->radius);
	this->radiusShape.setPosition(x - this->radius - 10.f, y - this->radius);
}

TowerFly::~TowerFly()
{
}

