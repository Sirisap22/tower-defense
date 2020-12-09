#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class MovementComponent
{
public: 
	enum class MovementState {
		IDLE,
		LEFT,
		RIGHT
	};
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	MovementState movementState;

	sf::Vector2f velocity;
	

	//Initializer functions

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float decleration);
	virtual ~MovementComponent();

	// Accessors
	const sf::Vector2f& getVelocity() const;

	// Functions
	const MovementState getMovementState() const;
	void setMovementState(MovementState state);
	
	void move(const float x, const float y, const float dt);
	void update(const float& dt);
};
#endif

