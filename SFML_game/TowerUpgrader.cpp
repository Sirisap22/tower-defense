#include "TowerUpgrader.h"

void TowerUpgrader::initTexture()
{
	if (!this->texture.loadFromFile("public/sprites/tower-upgrader/upgrader.png")) {
		throw "ERROR::COULD_NOT_LOAD_UPGRADER_TEXTURE";
	}
}

TowerUpgrader::TowerUpgrader(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->initTexture();
	this->shape.setTexture(this->texture);
}

TowerUpgrader::~TowerUpgrader()
{
}

bool TowerUpgrader::isPressed(sf::Vector2f mousePos)
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

void TowerUpgrader::upgraderTower(int selectedTower, int* money, std::vector<Tower*>* towers)
{
	if (selectedTower != -1) {
		Tower* tower = towers->at(selectedTower);
		if (tower->level == 3 || *money < 200) {
			return;
		}
		std::cout << "TEST\n";
		*money -= 200;
		tower->upgrade(tower->level + 1);
	}
}

void TowerUpgrader::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
