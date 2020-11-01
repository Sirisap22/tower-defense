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
	std::vector<std::string> towerCatUpper = { "NORMAL", "HEAVY", "FLY" };
	for (int j = 0; j < 3; ++j) {
		for (int i = 1; i <= 3; ++i) {
			std::string towerKey = "TOWER_" + towerCatUpper[j] + "_LEVEL_" + std::to_string(i);
			std::string bulletKey = "TOWER_" + towerCatUpper[j] + "_BULLET_" + std::to_string(i);
			std::string towerPath = "public/sprites/tower/" + towerCat[j] + "/level_" + std::to_string(i) + ".png";
			std::string bulletPath = "public/sprites/tower/" + towerCat[j] + "/bull_" + std::to_string(i) + ".png";
			if (!this->textures[towerKey].loadFromFile(towerPath))
			{
				throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TOWER_TEXTURE";
			}

			if (!this->textures[bulletKey].loadFromFile(bulletPath))
			{
				throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TOWER_BULLET_TEXTURE";
			}
		}
	}
	
	// tower creator textures
	for (int i = 0; i < 3; ++i) {
		std::string creatorKey = "TOWER_CREATOR_" + towerCatUpper[i];
		std::string creatorPath = "public/sprites/tower-creator/" + towerCat[i] + ".png";
		if (!this->textures[creatorKey].loadFromFile(creatorPath))
		{
			throw "ERROR::GAME_STATE::COULD_NOT_LOAD_CREATOR_TEXTURE";
		}
	}
	
}

void GameState::initCreator()
{
	this->towerCreator["NORMAL"] = new TowerCreator(500.f, 825.f, 100.f, 250.f, this->textures["TOWER_CREATOR_NORMAL"]);
	this->towerCreator["FLY"] = new TowerCreator(700.f, 825.f, 100.f, 250.f, this->textures["TOWER_CREATOR_FLY"]);
	this->towerCreator["HEAVY"] = new TowerCreator(900.f, 825.f, 100.f, 250.f, this->textures["TOWER_CREATOR_HEAVY"]);
}

void GameState::initPlayer()
{
	this->player = new Player(0.f, 0.f, this->textures["PLAYER_SHEET"]);
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

	// delete later
	for (int i = 1; i < 2; ++i) {
		this->towersAtCurrentState.push_back(new TowerNormal(100*i, 200*i, 10, 10, this->textures["TOWER_NORMAL_LEVEL_1"], this->textures["TOWER_NORMAL_LEVEL_2"], this->textures["TOWER_NORMAL_LEVEL_3"]));
		this->towersAtCurrentState.push_back(new TowerHeavy(100 * 2 * i, 200 * 2 * i, 10, 10, this->textures["TOWER_HEAVY_LEVEL_1"], this->textures["TOWER_HEAVY_LEVEL_2"], this->textures["TOWER_HEAVY_LEVEL_3"]));
		this->towersAtCurrentState.push_back(new TowerFly(100 * 3 * i, 200 * 3 * i, 10, 10, this->textures["TOWER_FLY_LEVEL_1"], this->textures["TOWER_FLY_LEVEL_2"], this->textures["TOWER_FLY_LEVEL_3"]));
	}
	//this->towersAtCurrentState.push_back(new TowerNormal(100, 200, 10, 10, this->textures["TOWER_NORMAL_LEVEL_1"], this->textures["TOWER_NORMAL_LEVEL_2"], this->textures["TOWER_NORMAL_LEVEL_3"]));

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
	this->initCreator();
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
	for (auto& tower : this->towersAtCurrentState) {
		delete tower;
	}
	this->towersAtCurrentState.clear();

	auto it = this->towerCreator.begin();
	for (it = this->towerCreator.begin(); it != this->towerCreator.end(); ++it)
	{
		delete it->second;
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

	// tower creator
	for (auto& it : this->towerCreator)
	{
		it.second->update(this->mousePosView);
	}

	for (auto& monster : this->monstersAtLevelN) {
		monster->update(dt);
	}

	//this->monstersAtLevelN->update(dt);

	// delete later
	for (auto& tower : this->towersAtCurrentState) {
	tower->update(dt);
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

	// tower creator
	for (auto& it : this->towerCreator)
	{
		it.second->render(target);
	}

	// monsters
	if (!this->monstersAtLevelN.empty()) {
		for (auto& monster : this->monstersAtLevelN) {	
			monster->render(target);
		}
	}

	// towers
	//this->monstersAtLevelN->render(target);
	if (!this->towersAtCurrentState.empty()) {
		for (auto& tower : this->towersAtCurrentState) {
			tower->render(target);
		}
	}
	
}
