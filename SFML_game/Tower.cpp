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

bool Tower::canAttack()
{
	int delay = 1500 - attackSpeed;
	if (this->time.getElapsedTime() > sf::milliseconds(delay)) {
		this->time.restart();
		return true;
	}

	return false;
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


