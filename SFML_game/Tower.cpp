#include "Tower.h"
void Tower::initVariables(Entity::EntityAttributes attribute, int damage, int attack_speed)
{
	this->level = 1;
	this->damage = damage;
	this->attackSpeed = attack_speed;
	this->attribute = attribute;
	this->radius = 0.f;
	this->radiusShape.setOutlineColor(sf::Color::Green);
	this->radiusShape.setOutlineThickness(1.f);
	this->radiusShape.setFillColor(sf::Color::Transparent);
}

void Tower::initTextures(std::map<std::string, sf::Texture> textures)
{
	std::string volcab = this->selectTexturesByAttribute();

	for (int i = 1; i <= 3; ++i) {
		this->textureTowerLevelN.push_back(textures["TOWER_" + volcab + "_LEVEL_" + std::to_string(i)]);
	}
}

std::string Tower::selectTexturesByAttribute()
{
	switch (this->attribute) {
		case Entity::EntityAttributes::NORMAL :
			return "NORMAL";
			break;
		case Entity::EntityAttributes::FLY :
			return "FLY";
			break;
		case Entity::EntityAttributes::HEAVY :
			return "HEAVY";
			break;
	}
	return "NONE";
}

bool Tower::canAttack()
{
	if (this->clock.getElapsedTime() > sf::seconds(0.5f)) {
		this->clock.restart();
		return true;
	}
	return false;
}

Tower::Tower(float x, float y, Entity::EntityAttributes attribute ,int damage, int attack_speed, std::map<std::string, sf::Texture> textures)
{
	this->initVariables(attribute, damage, attack_speed);
	this->initTextures(textures);


	this->setTexture(this->textureTowerLevelN[0]);

	
	this->originPoint = sf::Vector2f(x - 10.f, y);
	this->setPositions(x - this->sprite.getTexture()->getSize().x/2, y - this->sprite.getTexture()->getSize().y + 30.f);
}

Tower::~Tower()
{
}

bool Tower::isAlreadyDetected(Monster* monster)
{
	return (std::find(this->monstersInRadius.begin(), this->monstersInRadius.end(), monster) != this->monstersInRadius.end());
}

std::vector<Monster*>::iterator Tower::monsterIterator(Monster* monster)
{
	auto it = std::find(this->monstersInRadius.begin(), this->monstersInRadius.end(), monster);

	return it;
}

void Tower::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Tower::update(const float& dt)
{
}

void Tower::upgrade(int level)
{
	switch (level) {
	case 2:
		this->level = 2;
		this->damage = damage * 2;
		this->attackSpeed *= 2;
		this->sprite.setTexture(this->textureTowerLevelN[1]);
		break;
	case 3:
		this->level = 3;
		this->damage = damage * 1.5;
		this->attackSpeed *= 1.5;
		this->sprite.setTexture(this->textureTowerLevelN[2]);
		break;
	}

}



