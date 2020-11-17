#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class InputField
{
private:
	sf::RectangleShape field;
	sf::RectangleShape cursor;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color focusColor;

public:
	InputField(float x, float y, float width, float height,
		sf::Font* font, unsigned character_size);
	virtual ~InputField();

	void updateField(std::string str);
	void updateFocusState(const float dt);

};

