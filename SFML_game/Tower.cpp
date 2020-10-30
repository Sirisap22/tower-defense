#include "Tower.h"

void Tower::initVariables(int damage, int attack_speed)
{
	this->level = 1;
	this->damage = damage;
	this->attackSpeed = attack_speed;
}

//void Tower::initTextures(sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3)
//{
//	this->textureTowerLevelN[0] = level_1;
//	this->textureTowerLevelN[1] = level_2;
//	this->textureTowerLevelN[2] = level_3;
//}

Tower::Tower(float x, float y,int damage, int attack_speed, sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3)
{
	this->initVariables(damage, attack_speed);
	//this->initTextures(level_1, level_2, level_3);

	//this->setTexture(this->textureTowerLevelN[0]);

	this->setPositions(x, y);
}

Tower::~Tower()
{
}

void Tower::update(const float& dt)
{
}
