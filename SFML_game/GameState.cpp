#include "GameState.h"

// Initializer
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("public/sprites/player/idle.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}

	// monsters textures
	if (!this->textures["MONSTER_NORMAL_SHEET"].loadFromFile("public/sprites/monster/normal/mon-nor-walk.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MONSTER_TEXTURE";
	}
	if (!this->textures["MONSTER_HEAVY_SHEET"].loadFromFile("public/sprites/monster/heavy/mon-heavy-walk.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MONSTER_TEXTURE";
	}
	if (!this->textures["MONSTER_FLY_SHEET"].loadFromFile("public/sprites/monster/fly/mon-fly-walk.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MONSTER_TEXTURE";
	}

	// towers textures
	std::vector<std::string> towerCat = { "normal", "heavy", "fly" };
	for (std::string category : towerCat) {
		for (int i = 1; i <= 3; ++i) {
			std::string towerPath = "public/sprites/tower/" + category + "/level_" + std::to_string(i) + ".png";
			std::string bulletPath = "public/sprites/tower/" + category + "/bull_" + std::to_string(i) + ".png";
			if (!this->textures["TOWER_NORMAL_LEVEL_" + std::to_string(i)].loadFromFile(towerPath))
			{
				throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TOWER_TEXTURE";
			}

			if (!this->textures["TOWER_NORMAL_BULLET_" + std::to_string(i)].loadFromFile(bulletPath))
			{
				throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TOWER_BULLET_TEXTURE";
			}
		}
	}
	
	
	
}

void GameState::initPlayer()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initLevel()
{
	this->level = 1;

	//this->monstersAtLevelN[0] = new MonsterNormal(this->window->getSize().x - 1000, this->window->getSize().y - 1000, 100, "land", 100.f, 10, this->textures["MONSTER_NORMAL_SHEET"]);
	
	// init normal monsters
	for (int i = 0; i < 1; ++i) {
		this->monstersAtLevelN.push_back(new MonsterNormal(this->window->getSize().x - 1000, this->window->getSize().y - 1000, 100, "land", 100.f, 10, this->textures["MONSTER_NORMAL_SHEET"]));
	}

	// init heavy monsters
	for (int i = 0; i < 1; ++i) {
		this->monstersAtLevelN.push_back(new MonsterHeavy(100 * 2 * (i+1) , 100 * 2 * (i + 1), 100, "heavy", 100.f, 10, this->textures["MONSTER_HEAVY_SHEET"]));
	}

	// init fly monsters
	for (int i = 0; i < 2; ++i) {
		this->monstersAtLevelN.push_back(new MonsterFly(100 * 2 * (i + 1), 100 * 2 * (i + 1), 100, "fly", 100.f, 10, this->textures["MONSTER_FLY_SHEET"]));
	}


}

void GameState::incrementLevel()
{

}

void GameState::startLevel()
{
}



// Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();

	this->texture.loadFromFile("public/bg-game.png");
	this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->bg.setTexture(&texture);

	this->initPlayer();
	this->initLevel();

}

GameState::~GameState()
{

	delete this->player;

	for (auto& monster : this->monstersAtLevelN) {
		delete monster;
	}

	this->monstersAtLevelN.clear();

	//delete this->monstersAtLevelN;
}

void GameState::updateInput(const float& dt)
{

	// Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move( 0.f, 1.f, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->player->update(dt);

	for (auto& monster : this->monstersAtLevelN) {
		monster->update(dt);
	}

	//this->monstersAtLevelN->update(dt);

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->bg);

	this->player->render(target);

	if (!this->monstersAtLevelN.empty()) {
		for (auto& monster : this->monstersAtLevelN) {	
			monster->render(target);
		}
	}

	//this->monstersAtLevelN->render(target);
	
}
