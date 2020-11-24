#include "TowerFly.h"

TowerFly::TowerFly(float x, float y, Entity::EntityAttributes attribute, int damage, int attack_speed, std::map<std::string, sf::Texture> textures)
	:Tower(x, y, attribute, damage, attack_speed, textures)
{
	this->radius = 500.f;

	this->radiusShape.setRadius(this->radius);
	this->radiusShape.setPosition(x - this->radius - 10.f, y - this->radius);

	delete this->getHitboxComponent();
	this->createHitboxComponent(x - this->sprite.getTexture()->getSize().x / 2 - 20.f, y - this->sprite.getTexture()->getSize().y - 30.f, 100.f);
}

TowerFly::~TowerFly()
{
}

void TowerFly::upgrade(int level) {
	switch (level) {
	case 2:
		this->level = 2;
		this->damage = damage * 2;
		this->attackSpeed *= 2;
		this->sprite.setTexture(this->textureTowerLevelN[1], true);
		this->sprite.setPosition(this->originPoint.x - this->sprite.getTexture()->getSize().x / 2 + 10.f,
			this->originPoint.y - this->sprite.getTexture()->getSize().y + 30.f);
		break;
	case 3:
		this->level = 3;
		this->damage = damage * 1.5;
		this->attackSpeed *= 1.5;
		this->sprite.setTexture(this->textureTowerLevelN[2], true);
		this->sprite.setPosition(this->originPoint.x - this->sprite.getTexture()->getSize().x / 2 + 9.f,
			this->originPoint.y - this->sprite.getTexture()->getSize().y + 30.f);
		break;
	}
}

