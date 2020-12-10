#include "TowerArea.h"

TowerArea::TowerArea(float x, float y, float radius)
{
	this->area.setPosition(x, y);
	this->area.setOutlineColor(sf::Color::Red);
	this->area.setOutlineThickness(1.f);
	this->area.setFillColor(sf::Color::Transparent);
	this->area.setRadius(radius);

	this->originPoint = sf::Vector2f(x + this->area.getGlobalBounds().width / 2, y + this->area.getGlobalBounds().height / 2);
	this->isCreated = false;
}

TowerArea::~TowerArea()
{
}

const bool TowerArea::isTowerCreated() const
{
	return this->isCreated;
}

const sf::FloatRect TowerArea::getGlobalBound() const
{
	return this->area.getGlobalBounds();
}

const sf::Vector2f TowerArea::getOriginPoint() const
{
	return this->originPoint;
}

bool TowerArea::isPressed(sf::Vector2f mousePos)
{
	if (this->clock.getElapsedTime() > sf::seconds(60.f)) {
		this->clock.restart();
	}
	if (this->clock.getElapsedTime() > sf::seconds(0.2f) &&
		this->area.getGlobalBounds().contains(mousePos) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->clock.restart();
		return true;
	}
	return false;
}

void TowerArea::updateIsCreated(bool isCreated)
{
	this->isCreated = isCreated;
}

void TowerArea::render(sf::RenderTarget* target)
{
	target->draw(this->area);
}
