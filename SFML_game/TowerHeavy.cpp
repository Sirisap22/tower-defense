#include "TowerHeavy.h"

TowerHeavy::TowerHeavy(float x, float y, int damage, int attack_speed, sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3)
	:Tower(x, y, damage, attack_speed, level_1, level_2, level_3)
{
}

TowerHeavy::~TowerHeavy()
{
}
