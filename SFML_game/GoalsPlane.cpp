#include "GoalsPlane.h"

void GoalsPlane::initHeader(unsigned header_character_size)
{
	std::string header = "GOALS";
	this->header.setFont(*this->font);
	this->header.setString(header);
	this->header.setCharacterSize(header_character_size);
	//this->header.setFillColor(sf::Color(250, 250, 250, 250));
	this->header.setFillColor(sf::Color::Yellow);
	this->header.setOutlineThickness(1.f);
	this->header.setOutlineColor(sf::Color::Black);
	this->header.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->header.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + 10.f
	);
}

void GoalsPlane::initContent(unsigned content_character_size)
{
	this->content.setFont(*this->font);
	this->content.setString("- Prevent health from falling to 0. \n- Kill monsters to get points for the highest score.");
	this->content.setCharacterSize(content_character_size);
	this->content.setFillColor(sf::Color(250, 250, 250, 250));
	this->content.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->content.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->content.getGlobalBounds().height / 2.f + 30.f
	);
	this->content.setOutlineThickness(1.f);
	this->content.setOutlineColor(sf::Color::Black);
}

GoalsPlane::GoalsPlane(float x, float y, float width, float height, sf::Font* font, unsigned header_character_size, unsigned content_character_size)
	:	Plane(x, y, width, height, font, header_character_size, content_character_size)
{
	this->font = font;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(sf::Color(70, 70, 70, 200));
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Black);

	this->initHeader(header_character_size);
	this->initContent(content_character_size);
}

GoalsPlane::~GoalsPlane()
{
}
