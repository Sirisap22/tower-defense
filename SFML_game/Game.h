#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Game
{
	public:
		Game();
		void run();

	private:
		void processEvents();
		void update(sf::Time deltaTime);
		void render();
		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	private:
		sf::RenderWindow* mWindow;
		Player* mPlayer;
};


