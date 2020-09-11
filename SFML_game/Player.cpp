#include "Player.h"

void Player::initialTexture()
{
	if (!this->texture.loadFromFile("img/player/idle/1.png")) {
		std::cout << "error loading player texture";
	}
}

void Player::initialSprite()
{
	this->sprite.setTexture(this->texture);
}

Player::Player()
{
	this->initialTexture();
	this->initialSprite();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this -> sprite);
}
