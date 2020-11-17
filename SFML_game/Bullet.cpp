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
	this->createHitboxComponent(this->origin.x, this->origin.y, 10.f);
//	this->createMovementComponent(100.f, 10.f, 0.f);
}

void Bullet::initTextures(std::map<std::string, sf::Texture> textures)
{
	std::string volcab = this->selectTexturesByAttribute();

	for (int i = 1; i <= 3; ++i) {
		this->textureBulletLevelN.push_back(textures["TOWER_" + volcab + "_BULLET_" + std::to_string(i)]);
	}
}

Bullet::Bullet(float x, float y, Entity::EntityAttributes attribute, int level, Monster* target, std::map<std::string, sf::Texture> textures)
{
	this->attribute = attribute;
	this->level = level;
	this->target = target;
	this->isCollide = false;

	this->setPositions(x, y);
	this->origin = sf::Vector2f(x, y);

	this->initTextures(textures);

	this->setTextureByLevel();

	this->initComponents();


	//this->rotateRelativeTextureAngle();
}

Bullet::~Bullet()
{
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

sf::Sprite* Bullet::getSprite()
{
	return &this->sprite;
}

Monster* Bullet::getTarget() const
{
	return this->target;
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




void Bullet::update(const float& dt,float angle)
{
	//this->movementComponent->update(dt);
	//this->sprite.rotate(angle);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

