#include "InputField.h"

InputField::InputField(sf::RenderWindow* window, float x, float y, float width, float height, sf::Font* font, unsigned character_size)
{

	this->window = window;
	this->characterSize = character_size;
	this->font = font;

	// init field and cursor

	// size
	this->field.setSize(sf::Vector2f(width, height));
	this->cursor.setSize(sf::Vector2f(1.f, height - 2.f));

	// color
	this->field.setFillColor(sf::Color::White);
	this->field.setOutlineThickness(1.f);
	this->field.setOutlineColor(sf::Color::Black);

	this->cursor.setFillColor(sf::Color::Black);

	// position
	this->field.setPosition(sf::Vector2f(x, y));
	this->cursor.setPosition(sf::Vector2f(x + 2.f, y + 2.f));

	this->isFocus = false;

	// font

	this->text.setPosition(sf::Vector2f(x + 1.f, y + 1.f));
	this->text.setFont(*this->font);
	this->text.setCharacterSize(this->characterSize);
	this->text.setFillColor(sf::Color::Black);

	// sound
	if (!this->keyType.loadFromFile("public/sounds/key_type.wav")) {
		throw("ERROR::INPUTFIELD::COULD_NOT_LOAD_SOUND");
	}

	this->typing.setBuffer(this->keyType);
	this->typing.setVolume(50.f);
}

InputField::~InputField()
{
}

const std::string InputField::getName() const
{
	return this->name;
}

void InputField::updateField()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window->close();
		if (this->isFocus && this->event.type == sf::Event::TextEntered && this->event.text.unicode < 128) {
			switch (event.key.code) {
				case 32:
					break;
				case 8:
					if (this->name.size() == 0) {
						break;
					}
					this->name.pop_back();
					this->typing.play();
					this->text.setString(this->name);
					break;
				default:
					if (this->name.size() >= 15) break;
					this->name += event.text.unicode;
					// play sound
					this->typing.play();
					this->text.setString(this->name);
			}

			// update cursor 
			this->cursor.setPosition(this->text.getPosition().x + this->text.getGlobalBounds().width + 2.f, this->cursor.getPosition().y);
		}

	}
	
}

void InputField::updateFocusState(const sf::Vector2f mousePos)
{
	if (this->clock.getElapsedTime() > sf::seconds(0.2f) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->clock.restart();
		if (this->field.getGlobalBounds().contains(mousePos)) {
			this->isFocus = true;
		}
		else {
			this->isFocus = false;
		}
	}
}

void InputField::update(const float& dt, const sf::Vector2f mousePos)
{
	this->dt = dt;
	this->updateFocusState(mousePos);
	this->updateField();
}

void InputField::render(sf::RenderTarget* target)
{
	target->draw(this->field);
	target->draw(this->text);
	if (this->isFocus ) {
		target->draw(this->cursor);
	}
}
