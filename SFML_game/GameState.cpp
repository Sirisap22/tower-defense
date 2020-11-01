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
	this->selectedTowerCreator = TowerCreator::TowerType::NONE;
	this->towerCreator["NORMAL"] = new TowerCreator(500.f, 825.f, 100.f, 250.f, TowerCreator::TowerType::NORMAL, this->textures["TOWER_CREATOR_NORMAL"]);
	this->towerCreator["FLY"] = new TowerCreator(700.f, 825.f, 100.f, 250.f, TowerCreator::TowerType::FLY, this->textures["TOWER_CREATOR_FLY"]);
	this->towerCreator["HEAVY"] = new TowerCreator(900.f, 825.f, 100.f, 250.f, TowerCreator::TowerType::HEAVY, this->textures["TOWER_CREATOR_HEAVY"]);
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
	for (int i = 0; i < 2; ++i) {
		this->monstersAtLevelN.push_back(new MonsterNormal(this->window->getSize().x - 1000, this->window->getSize().y - 1000, Entity::EntityAttributes::NORMAL, 100, 100.f, 10, this->textures["MONSTER_NORMAL_SHEET"]));
	}

	// init heavy monsters
	for (int i = 0; i < 1; ++i) {
		this->monstersAtLevelN.push_back(new MonsterHeavy(100, 100, Entity::EntityAttributes::HEAVY, 100, 100.f, 10, this->textures["MONSTER_HEAVY_SHEET"]));
	}

	// init fly monsters
	for (int i = 0; i < 2; ++i) {
		this->monstersAtLevelN.push_back(new MonsterFly(100 * 2 * (i + 1), 100 * 2 * (i + 1), Entity::EntityAttributes::FLY, 100, 100.f, 10, this->textures["MONSTER_FLY_SHEET"]));
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

void GameState::checkAndCreateTower()
{
	if (this->selectedTowerCreator != TowerCreator::TowerType::NONE && this->mousePosView.y < 800 && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		switch (this->selectedTowerCreator) {
		case TowerCreator::TowerType::NORMAL:
			this->towersAtCurrentState.push_back(new TowerNormal(this->mousePosView.x, this->mousePosView.y, Entity::EntityAttributes::NORMAL, 10, 10, this->textures["TOWER_NORMAL_LEVEL_1"], this->textures["TOWER_NORMAL_LEVEL_2"], this->textures["TOWER_NORMAL_LEVEL_3"]));
			this->selectedTowerCreator = TowerCreator::TowerType::NONE;
			break;
		case TowerCreator::TowerType::FLY:
			this->towersAtCurrentState.push_back(new TowerFly(this->mousePosView.x, this->mousePosView.y, Entity::EntityAttributes::FLY, 10, 10, this->textures["TOWER_FLY_LEVEL_1"], this->textures["TOWER_FLY_LEVEL_2"], this->textures["TOWER_FLY_LEVEL_3"]));
			this->selectedTowerCreator = TowerCreator::TowerType::NONE;
			break;
		case TowerCreator::TowerType::HEAVY:
			this->towersAtCurrentState.push_back(new TowerHeavy(this->mousePosView.x, this->mousePosView.y, Entity::EntityAttributes::HEAVY, 10, 10, this->textures["TOWER_HEAVY_LEVEL_1"], this->textures["TOWER_HEAVY_LEVEL_2"], this->textures["TOWER_HEAVY_LEVEL_3"]));
			this->selectedTowerCreator = TowerCreator::TowerType::NONE;
			break;
		default:
			std::cout << "NONE" << std::endl;
		}
	}
}

bool GameState::isMonsterInTowerRadius(float towerRadius,float towerX, float towerY, float monsterX, float monsterY)
{
	std::cout << "towerX: " << towerX << " towerY: " << towerY << " monsterX: " << monsterX << " monsterY: " << monsterY << std::endl;
	std::cout << (towerX - monsterX) * (towerX - monsterX) + (towerY - monsterY) * (towerY - monsterY) << " distance \n ";
	std::cout << "radius " << towerRadius*towerRadius << std::endl;
	return (towerX - monsterX) * (towerX - monsterX) + (towerY - monsterY) * (towerY - monsterY) < towerRadius * towerRadius;
}

void GameState::checkMonstersInTowersRadius()
{
	for (auto& tower : this->towersAtCurrentState) {
		for (auto& monster : this->monstersAtLevelN) {
			if (
				tower->attribute == monster->attribute && 
				isMonsterInTowerRadius(tower->radius, tower->originPoint.x, tower->originPoint.y, monster->originPoint.x, monster->originPoint.y) &&
				!tower->isAlreadyDetected(monster)
				) {
				tower->monstersInRadius.push_back(monster);
				// delete later
				std::cout << "Detected\n";
				//tower->monstersInRadius.erase(tower->monstersInRadius.begin());
			}
		}
	}
}

void GameState::checkMonstersOutTowersRadius()
{
	for (auto& tower : this->towersAtCurrentState) {
		for (int i = 0; i < tower->monstersInRadius.size(); ++i) {
			Monster* monster = tower->monstersInRadius[i];
			if (!isMonsterInTowerRadius(tower->radius, tower->originPoint.x, tower->originPoint.y, monster->originPoint.x, monster->originPoint.y)) {
				tower->monstersInRadius.erase(tower->monstersInRadius.begin() + i);
			}
		}
	}
}

void GameState::updateTowersAndMonstersInteraction()
{
	if (!this->towersAtCurrentState.empty()) {
		checkMonstersInTowersRadius();
		checkMonstersOutTowersRadius();
	}
	
}

void GameState::updateTowerCreator(const float& dt)
{
	for (auto& towerCreator : this->towerCreator) {
		if (towerCreator.second->isPressed()) {
			// toggle selected item
			if (this->selectedTowerCreator == towerCreator.second->selectedTowerType() && this->selectedTowerCreator != TowerCreator::TowerType::NONE) {
				this->selectedTowerCreator = TowerCreator::TowerType::NONE;
			}
			else {
				this->selectedTowerCreator = towerCreator.second->selectedTowerType();
			}

			// delete later 
			switch(this->selectedTowerCreator) {
				case TowerCreator::TowerType::NORMAL:
					std::cout << "NORMAL" << std::endl;
					break;
				case TowerCreator::TowerType::FLY:
					std::cout << "FLY" << std::endl;
					break;
				case TowerCreator::TowerType::HEAVY:
					std::cout << "HEAVY" << std::endl;
					break;
				case TowerCreator::TowerType::NONE:
					std::cout << "NONE" << std::endl;

			}
			
		}
	}

	checkAndCreateTower();
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
		it.second->update(this->mousePosView, dt);
	}

	this->updateTowerCreator(dt);

	for (auto& monster : this->monstersAtLevelN) {
		monster->update(dt);
	}

	//this->monstersAtLevelN->update(dt);

	// delete later
	for (auto& tower : this->towersAtCurrentState) {
	tower->update(dt);
	}

	this->updateTowersAndMonstersInteraction();

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
