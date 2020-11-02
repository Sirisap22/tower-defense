#include "TowerCreator.h"


TowerCreator::TowerCreator(float x, float y, float width, float height, TowerType tower_type, sf::Texture& texture)
{
	this->towerCreatorState = states::BTN_IDLE;
	this->towerTypeToCreator = tower_type;
	
	//this->shape.setSc(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setTexture(texture);
}

TowerCreator::~TowerCreator()
{
}

const bool TowerCreator::isPressed() const
{
	if (this->towerCreatorState == states::BTN_ACTIVE) {
		//std::cout << "TRUE\n";
		return true;
	}
	return false;
}

const TowerCreator::TowerType TowerCreator::selectedTowerType() const
{
	return this->towerTypeToCreator;
}

void TowerCreator::update(const sf::Vector2f mousePos, const float& dt)
{
	
	this->towerCreatorState = states::BTN_IDLE;

	// make sure clock to not overflow
	if (this->clock.getElapsedTime() > sf::seconds(30.f)) {
		this->clock.restart();
	}

	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->towerCreatorState = states::BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->clock.getElapsedTime() > sf::seconds(0.2f) && !this->isPressed()) {
			//std::cout << "ACTIVE\n";
			this->clock.restart();
			this->towerCreatorState = states::BTN_ACTIVE;
		}
	}
}

void TowerCreator::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
