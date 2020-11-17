#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Tower.h";
class TowerUpgrader
{
private:
	sf::Sprite shape;
	sf::Texture texture;
	sf::Clock clock;

	void initTexture();
public:
	TowerUpgrader(float x, float y);
	virtual ~TowerUpgrader();

	bool isPressed(sf::Vector2f mousePos);

	void upgraderTower(int selectedTower,int* money, std::vector<Tower*>* towers);
	void render(sf::RenderTarget* target);
};

