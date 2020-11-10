#include "Bullet.h"

std::string Bullet::selectTexturesByAttribute()
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

void Bullet::initComponents()
{
	this->createHitboxComponent(this->origin.x - 20.f, this->origin.y, 50.f);
}

void Bullet::initTextures(std::map<std::string, sf::Texture> textures)
{
	std::string volcab = this->selectTexturesByAttribute();

	for (int i = 1; i <= 3; ++i) {
		this->textureBulletLevelN.push_back(textures["TOWER_" + volcab + "_BULLET_" + std::to_string(i)]);
	}
}

Bullet::Bullet(float x, float y, Entity::EntityAttributes attribute, int level, Tower* tower, Monster* target, std::map<std::string, sf::Texture> textures)
{
	this->attribute = attribute;
	this->level = level;
	this->tower = tower;
	this->target = target;

	this->setPositions(x, y);
	this->origin = sf::Vector2f(x, y);

	this->initTextures(textures);

	this->setTextureByLevel();

	this->initComponents();

	this->rotateRelativeTextureAngle();
}

Bullet::~Bullet()
{
}

Tower* Bullet::getTower() const
{
	return this->tower;
}

Monster* Bullet::getTarget() const
{
	return this->target;
}

void Bullet::setTextureByLevel()
{
	switch (this->level) {
		case 1:
			this->setTexture(this->textureBulletLevelN[0]);
			break;
		case 2:
			this->setTexture(this->textureBulletLevelN[1]);
			break;
		case 3:
			this->setTexture(this->textureBulletLevelN[2]);
			break;
		default:
			throw "ERROR::CANNOT::SET::BULLET::TEXTURE";
	}
}

sf::Vector2f Bullet::relativeTargetPosition()
{
	sf::Vector2f bulletHitboxPosition = this->getHitboxComponent()->getHitbox().getPosition();
	sf::Vector2f monsterHitboxPosition = this->target->getHitboxComponent()->getHitbox().getPosition();
	sf::FloatRect bulletHitboxShape = this->getHitboxComponent()->getHitbox().getGlobalBounds();
	sf::FloatRect monsterHitboxShape = this->target->getHitboxComponent()->getHitbox().getGlobalBounds();

	float dx = (bulletHitboxPosition.x + (bulletHitboxShape.width / 2)) - (monsterHitboxPosition.x + (monsterHitboxShape.width / 2));
	float dy = (bulletHitboxPosition.y + (bulletHitboxShape.height / 2)) - (monsterHitboxPosition.y + (monsterHitboxShape.height / 2));

	return sf::Vector2f(dx, dy);
}

void Bullet::rotateRelativeTextureAngle()
{
	sf::Vector2f diff = this->relativeTargetPosition();
	float dx = diff.x;
	float dy = diff.y;
	float angle = 0.f;
	// top left
	if (dx > 0.f && dy > 0.f) {
		angle = -std::atan(dy / dx);
	}
	// top right
	else if (dx < 0.f && dy > 0.f) {
		angle = std::atan(dy / dx);
	}
	// bottom left
	else if (dx > 0.f && dy < 0.f) {
		angle = -(std::atan(dy / dx) + 90.f);
	} 
	// bottom right
	else if (dx < 0.f && dy < 0.f) {
		angle = std::atan(dy / dx) + 90.f;
	}

	this->sprite.setRotation(angle);
}



void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Bullet::shoot(const float& dt)
{
	this->rotateRelativeTextureAngle();
	//sf::Vector2f pos = this->relativeTargetPosition();
	//std::cout << pos.x << " " << pos.y << std::endl;
	this->sprite.setPosition(this->target->getHitboxComponent()->getHitbox().getPosition());
}
