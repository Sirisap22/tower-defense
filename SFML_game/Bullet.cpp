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
	this->createHitboxComponent(this->origin.x - 30.f, this->origin.y, 10.f);
//	this->createMovementComponent(100.f, 10.f, 0.f);
}

void Bullet::initTextures(std::map<std::string, sf::Texture> textures)
{
	std::string volcab = this->selectTexturesByAttribute();

	for (int i = 1; i <= 3; ++i) {
		this->textureBulletLevelN.push_back(textures["TOWER_" + volcab + "_BULLET_" + std::to_string(i)]);
	}
}

Bullet::Bullet(float x, float y, Entity::EntityAttributes attribute, int level, int damage, Monster* target, std::map<std::string, sf::Texture> textures)
{
	this->attribute = attribute;
	this->level = level;
	this->target = target;
	this->isCollide = false;
	this->damage = damage;

	this->setPositions(x, y);
	this->origin = sf::Vector2f(x, y);

	this->initTextures(textures);

	this->setTextureByLevel();

	this->initComponents();

	if (target) {
		auto pos = this->relativeTargetPosition();
		std::cout << "pos : " << pos << std::endl;
		this->sprite.setRotation(pos);
	}

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

float Bullet::relativeTargetPosition()
{
	sf::Vector2f bulletHitboxPosition = this->getHitboxComponent()->getHitbox().getPosition();
	sf::Vector2f monsterHitboxPosition = this->target->getHitboxComponent()->getHitbox().getPosition();
	sf::FloatRect bulletHitboxShape = this->getHitboxComponent()->getHitbox().getGlobalBounds();
	sf::FloatRect monsterHitboxShape = this->target->getHitboxComponent()->getHitbox().getGlobalBounds();

	float bX = (bulletHitboxPosition.x + (bulletHitboxShape.width / 2));
	float bY = (bulletHitboxPosition.y + (bulletHitboxShape.height / 2));
	float mX = (monsterHitboxPosition.x + (monsterHitboxShape.width / 2));
	float mY = (monsterHitboxPosition.y + (monsterHitboxShape.height / 2));

	//float dx = (bulletHitboxPosition.x + (bulletHitboxShape.width / 2)) - (monsterHitboxPosition.x + (monsterHitboxShape.width / 2));
	//float dy = (bulletHitboxPosition.y + (bulletHitboxShape.height / 2)) - (monsterHitboxPosition.y + (monsterHitboxShape.height / 2));

	float upper = bX * mX + bY * mY;
	float lower = std::sqrtf(bX * bX + bY * bY) * std::sqrtf(mX * mX + mY * mY);
	float theta = std::acosf(upper / lower) * 180.f / float(M_PI);
	if (bX - mX > 0) return -90.f + theta;
	//std::cout << "theta : " << theta << std::endl;
	return 90.f - theta;
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

