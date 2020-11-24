#include "InputFieldPlane.h"

void InputFieldPlane::initHeader(unsigned header_character_size)
{
	std::string header = "ENTER NAME";
	this->header.setFont(*this->font);
	this->header.setString(header);
	this->header.setCharacterSize(header_character_size);
	this->header.setFillColor(sf::Color(250, 250, 250, 250));
	this->header.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->header.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + 10.f
	);
}

void InputFieldPlane::initContent(unsigned content_character_size)
{

}

InputFieldPlane::InputFieldPlane(float x, float y, float width, float height, sf::Font* font, unsigned header_character_size, unsigned content_character_size)
	: Plane (x, y, width, height, font, header_character_size, content_character_size)
{
	this->initHeader(header_character_size);
}

InputFieldPlane::~InputFieldPlane()
{
}

void InputFieldPlane::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->header);
}
