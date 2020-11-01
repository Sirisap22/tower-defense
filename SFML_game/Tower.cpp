#include "Tower.h"

void Tower::initVariables(Entity::EntityAttributes attribute, int damage, int attack_speed)
{
	this->level = 1;
	this->damage = damage;
	this->attackSpeed = attack_speed;
	this->attribute = attribute;
}

void Tower::initTextures(sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3)
{
	this->textureTowerLevelN.push_back(level_1);
	this->textureTowerLevelN.push_back(level_2);
	this->textureTowerLevelN.push_back(level_3);

	
}

Tower::Tower(float x, float y, Entity::EntityAttributes attribute ,int damage, int attack_speed, sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3)
{
	this->initVariables(attribute, damage, attack_speed);
	this->initTextures(level_1, level_2, level_3);

	this->setTexture(this->textureTowerLevelN[0]);

	this->originPoint = sf::Vector2f(x, y);
	this->setPositions(x - this->sprite.getTexture()->getSize().x/2, y - this->sprite.getTexture()->getSize().y / 2);
}

Tower::~Tower()
{
}

bool Tower::isAlreadyDetected(Monster* monster)
{
	return (std::find(this->monstersInRadius.begin(), this->monstersInRadius.end(), monster) != this->monstersInRadius.end());
}

void Tower::update(const float& dt)
{
}
