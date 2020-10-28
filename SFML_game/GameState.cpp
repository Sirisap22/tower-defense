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
}

void GameState::initPlayer()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initLevel()
{
	this->level = 1;
	
	// init normal monsters
	for (int i = 0; i < 1; ++i) {
		this->monstersNormalAtLevelN.push_back(new MonsterNormal(this->window->getSize().x - 500, this->window->getSize().y - 500, 100, "land", 100.f, 10, this->textures["MONSTER_NORMAL_SHEET"]));
	}

	// init heavy monsters
	for (int i = 0; i < 1; ++i) {
		this->monstersHeavyAtLevelN.push_back(new MonsterHeavy(100 * 2 * (i+1) , 100 * 2 * (i + 1), 100, "heavy", 100.f, 10, this->textures["MONSTER_HEAVY_SHEET"]));
	}

	// init fly monsters
	for (int i = 0; i < 2; ++i) {
		this->monstersFlyAtLevelN.push_back(new MonsterFly(100 * 2 * (i + 1), 100 * 2 * (i + 1), 100, "fly", 100.f, 10, this->textures["MONSTER_FLY_SHEET"]));
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

	for (auto& monster_normal : this->monstersNormalAtLevelN) {
		delete monster_normal;
	}

	for (auto& monster_heavy : this->monstersHeavyAtLevelN) {
		delete monster_heavy;
	}

	for (auto& monster_fly : this->monstersFlyAtLevelN) {
		delete monster_fly;
	}
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

	for (auto& monster_normal : this->monstersNormalAtLevelN) {
		monster_normal->update(dt);
	}

	for (auto& monster_heavy : this->monstersHeavyAtLevelN) {
		monster_heavy->update(dt);
	}

	for (auto& monster_fly : this->monstersFlyAtLevelN) {
		monster_fly->update(dt);
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->bg);

	this->player->render(target);

	if (!this->monstersNormalAtLevelN.empty()) {
		for (auto& monster_normal : this->monstersNormalAtLevelN) {
			monster_normal->render(target);
		}
	}

	if (!this->monstersHeavyAtLevelN.empty()) {
		for (auto& monster_heavy : this->monstersHeavyAtLevelN) {
			monster_heavy->render(target);
		}
	}
	
	if (!this->monstersFlyAtLevelN.empty()) {
		for (auto& monster_fly : this->monstersFlyAtLevelN) {
			monster_fly->render(target);
		}
	}
	
}
