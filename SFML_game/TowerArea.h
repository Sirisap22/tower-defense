#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class TowerArea
{
private:
	sf::CircleShape area;
	sf::Vector2f originPoint;
	sf::Clock clock;
	bool isCreated;
public:
	TowerArea(float x, float y, float radius);
	virtual ~TowerArea();

	const bool isTowerCreated() const;
	const sf::FloatRect getGlobalBound() const;
	const sf::Vector2f getOriginPoint() const;
	bool isPressed(sf::Vector2f mousePos);

	void updateIsCreated(bool isCreated);
	void render(sf::RenderTarget* target);
};

