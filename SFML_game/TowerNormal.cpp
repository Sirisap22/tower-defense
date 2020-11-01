#include "TowerNormal.h"

TowerNormal::TowerNormal(float x, float y, Entity::EntityAttributes attribute, int damage, int attack_speed, sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3)
	:Tower(x, y, attribute, damage, attack_speed, level_1, level_2, level_3)
{
	this->radius = 100.f;
}

TowerNormal::~TowerNormal()
{
}
