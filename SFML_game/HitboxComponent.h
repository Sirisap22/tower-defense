#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class HitboxComponent
{
private:
	sf::CircleShape hitbox;
	sf::Vector2f originPoint;
public:
	HitboxComponent(float x, float y, float radius);
	virtual ~HitboxComponent();

	const sf::Vector2f& getOriginPoint() const;
	const sf::CircleShape& getHitbox() const;

	virtual void update(sf::Vector2f currentPosition, float adjustX, float adjustY);
};

