#include "TowerSeller.h"

void TowerSeller::initTexture()
{
	if (!this->texture.loadFromFile("public/sprites/tower-seller/seller.png")) {
		throw "ERROR::COULD_NOT_LOAD_SELLER_TEXTURE";
	}
}

TowerSeller::TowerSeller(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->initTexture();
	this->shape.setTexture(this->texture);
}

TowerSeller::~TowerSeller()
{
}

bool TowerSeller::isPressed(sf::Vector2f mousePos)
{
	if (this->clock.getElapsedTime() > sf::seconds(60.f)) {
		this->clock.restart();
	}
	if (this->clock.getElapsedTime() > sf::seconds(0.2f) &&
		this->shape.getGlobalBounds().contains(mousePos) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->clock.restart();
		return true;
	}
	return false;
}

void TowerSeller::sellTower(int selectedTower,int* money, std::vector<Tower*>* towers)
{
	if (selectedTower != -1) {
		std::cout << "TEST\n";
		*money += 150;
		delete towers->at(selectedTower);
		towers->erase(towers->begin() + selectedTower);
	}
}

void TowerSeller::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
