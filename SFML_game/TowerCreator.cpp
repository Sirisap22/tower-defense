#include "TowerCreator.h"

TowerCreator::TowerCreator(float x, float y, float width, float height, sf::Texture& texture)
{
	this->towerCreatorState = BTN_IDLE;
	
	//this->shape.setSc(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setTexture(texture);
}

TowerCreator::~TowerCreator()
{
}

const bool TowerCreator::isPressed() const
{
	if (this->towerCreatorState == BTN_ACTIVE) {
		return true;
	}
	return false;
}

void TowerCreator::update(const sf::Vector2f mousePos)
{
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->towerCreatorState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->towerCreatorState = BTN_ACTIVE;
			std::cout << "CLICKED" << std::endl;
		}
	}
}

void TowerCreator::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
