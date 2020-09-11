#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Player{
	private:
		sf::Sprite sprite;
		sf::Texture texture;

	private:
		void initialTexture();
		void initialSprite();

	public:
		Player();

	public:
		void update();
		void render(sf:: RenderTarget& target);
	
};

