#include "Button.h"



Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - 10
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->shape.setFillColor(this->idleColor);

	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(1.f);
}

Button::~Button()
{

}


// Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

const sf::FloatRect Button::getTextGlobalBounds() const
{
	return this->text.getGlobalBounds();
}

void Button::setButtonPosition(float x, float y)
{
	this->text.setPosition(x, y);
}

void Button::setShapePosition(float x, float y)
{
	this->shape.setPosition(x, y);
}


// Functions

void Button::update(const sf::Vector2f mousePos)
{
	/* Update the booleans for hover and pressed */
	
	// Idle
	this->buttonState = BTN_IDLE;

	// make sure clock to not overflow
	if (this->clock.getElapsedTime() > sf::seconds(60.f)) {
		this->clock.restart();
	}

	// Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		// Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->clock.getElapsedTime() > sf::seconds(0.2f) && !this->isPressed())
		{
			this->clock.restart();
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState) 
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}



}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
