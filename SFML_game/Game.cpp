#include "Game.h"


Game::Game() {
	this->mWindow = new sf::RenderWindow(sf::VideoMode(1080, 720), "SFML Application", sf::Style::Fullscreen);
	this->mWindow->setFramerateLimit(144);
	this->mPlayer = new Player;

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time TimePerFrame = sf::seconds(1.f / 30.f);
	while (this->mWindow->isOpen())
	{
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (this->mWindow->pollEvent(event))
	{
		switch (event.type) 
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				this->mWindow->close();
				break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{

}

// game loop

void Game::render()
{
	this->mWindow->clear();
	this->mPlayer->render(*this->mWindow);

	this->mWindow->display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

}