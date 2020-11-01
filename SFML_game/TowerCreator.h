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
public:
	enum class states { BTN_IDLE, BTN_HOVER, BTN_ACTIVE };
	enum class TowerType { NORMAL, FLY, HEAVY, NONE };
private:
	sf::Sprite shape;
	states towerCreatorState;
	TowerType towerTypeToCreator;
	sf::Clock clock;
public:
	TowerCreator(float x, float y, float width, float height,TowerType tower_type, sf::Texture& texture);
	~TowerCreator();

	// Accessors
	const bool isPressed() const;
	const TowerType selectedTowerType() const;

	//Functions
	void update(const sf::Vector2f mousePos, const float& dt);
	void render(sf::RenderTarget* target);
};

