#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
class InputField
{
private:
	sf::RenderWindow* window;
	sf::Clock clock;
	sf::Event event;
	sf::RectangleShape field;
	sf::RectangleShape cursor;
	sf::Font* font;
	sf::Text text;
	std::string name;
	sf::SoundBuffer keyType;
	sf::Sound typing;
	unsigned characterSize;
	bool isFocus;

public:
	InputField(sf::RenderWindow* window, float x, float y, float width, float height,
		sf::Font* font, unsigned character_size);
	virtual ~InputField();

	const std::string getName() const;

	void updateField();
	void updateFocusState(const sf::Vector2f mousePos);
	void update(const float& dt, const sf::Vector2f mousePos);

	void render(sf::RenderTarget* target);

};

