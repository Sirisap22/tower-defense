#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class HitboxComponent
{
private:
	sf::RectangleShape hitbox;
	sf::Vector2f originPoint;
public:
	HitboxComponent(float x, float y, float width, float height);
	virtual ~HitboxComponent();

	const sf::Vector2f& getOriginPoint() const;
	const sf::RectangleShape& getHitbox() const;

	virtual void update(const float& dt, sf::Vector2f currentPosition);
};

