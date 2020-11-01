#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Monster.h"
#include "MonsterNormal.h"
#include "MonsterFly.h"
#include "MonsterHeavy.h"
class TowerCreator
{

enum states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };
private:
	sf::Sprite shape;
	bool towerCreatorState;
public:
	TowerCreator(float x, float y, float width, float height, sf::Texture& texture);
	~TowerCreator();

	// Accessors
	const bool isPressed() const;

	//Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

