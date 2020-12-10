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
	sf::Text player;
	player.setString(this->playerName);
	player.setPosition(10.f, 10.f);
	player.setCharacterSize(42);
	player.setFont(this->font);
	player.setFillColor(sf::Color::White);
	this->textName = player;
	this->playerHealth = 100;
	sf::Text health;
	health.setString(std::to_string(this->playerHealth) + "/100");
	health.setPosition(50.f, 10.f);
	health.setCharacterSize(42);
	health.setFont(this->font);
	health.setFillColor(sf::Color::Red);
	this->textPlayerHealth = health;
	this->money = 3000;
	this->player = new Player(0.f, 0.f, this->textures["PLAYER_SHEET"]);
}

void GameState::initFont()
{
	if (!this->font.loadFromFile("Fonts/EvilEmpire-4BBVK.ttf")) {
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initButtons()
{
	this->buttons["TOGGLE_HITBOX"] = new Button(
		1600.f, 900.f, 200.f, 50.f,
		&this->font, "Toggle Hitbox", 24,
		sf::Color(250, 250, 250, 250), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 0)
	);
}

void GameState::initPausedButtons()
{
	this->pausedButtons["RESUME"] = new Button(
		300.f, 400.f, 200.f, 50.f,
		&this->font, "Resume", 72,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 100), sf::Color(70, 70, 70, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->pausedButtons["BACK_TO_MENU"] = new Button(
		300.f, 500.f, 200.f, 50.f,
		&this->font, "Back To Menu", 72,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 100), sf::Color(70, 70, 70, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void GameState::initPausedMenu()
{
	this->pausedPlane.setFillColor(sf::Color(70, 70, 70, 200));
	this->pausedPlane.setPosition(180.f, 0.f);
	this->pausedPlane.setSize(sf::Vector2f(440.f, this->window->getSize().y));

}

void GameState::initEndButtons()
{
	this->endButtons["BACK_TO_MENU"] = new Button(
		this->window->getSize().x/2, 570.f, 200.f, 50.f,
		&this->font, "Back To Menu", 72,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 100), sf::Color(70, 70, 70, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->endButtons["BACK_TO_MENU"]->setButtonPosition(this->window->getSize().x / 2 - this->endButtons["BACK_TO_MENU"]->getTextGlobalBounds().width / 2, 570.f);
}

void GameState::initEndMenu()
{
	this->endPlane.setFillColor(sf::Color(70, 70, 70, 200));
	this->endPlane.setPosition(this->window->getSize().x/2 - 440.f/2.f , 320.f);
	this->endPlane.setSize(sf::Vector2f(440.f, 430.f));

	this->endText.setString("Your Score");
	this->endText.setFont(this->font);
	this->endText.setCharacterSize(72);
	this->endText.setFillColor(sf::Color::White);
	this->endText.setPosition(this->window->getSize().x / 2 - this->endText.getGlobalBounds().width / 2, 350.f);

	this->scoreEndText.setFont(this->font);
	this->scoreEndText.setCharacterSize(72);
	this->scoreEndText.setFillColor(sf::Color::White);
	this->scoreEndText.setPosition(this->window->getSize().x / 2 - this->scoreEndText.getGlobalBounds().width / 2, 450.f);

}

void GameState::initScore()
{
	this->score = 0;
	this->textScore.setString(std::to_string(this->score));
	this->textScore.setPosition(1600.f, 30.f);
	this->textScore.setCharacterSize(48);
	this->textScore.setFont(this->font);
	this->textScore.setFillColor(sf::Color::White);
}

void GameState::initLevel()
{
	this->level = 0;

	this->textLevel.setPosition(800.f, 5.f);
	this->textLevel.setCharacterSize(18);
	this->textLevel.setFont(this->font);
	this->textLevel.setFillColor(sf::Color::White);
	this->textLevel.setString("Level "+std::to_string(this->level));

	this->selectedTower = -1;
	this->toggleHitbox = false;

	this->gold.setFont(this->font);
	this->gold.setString("GOLD : "+std::to_string(this->money));
	this->gold.setCharacterSize(48);
	this->gold.setPosition(sf::Vector2f(1600.f, 70.f));
	this->gold.setFillColor(sf::Color::Yellow);

	this->towerSeller = new TowerSeller(1400.f, 800.f);
	this->towerUpgrader = new TowerUpgrader(1200.f, 800.f);
	//this->monstersAtLevelN[0] = new MonsterNormal(this->window->getSize().x - 1000, this->window->getSize().y - 1000, 100, "land", 100.f, 10, this->textures["MONSTER_NORMAL_SHEET"]);
	
	this->totalMonstersAtCurrentTime = 0;
	this->totalMonstersAtLevelN = 5;
	this->spawnTimer.restart();

}



void GameState::initCountdown()
{
	this->countdown = 30;
	this->isWaveStarted = false;
	this->isCountdown = true;

	this->countdownText.setFont(this->font);
	this->countdownText.setCharacterSize(24);
	this->countdownText.setPosition(5.f, 1000.f);
	this->countdownText.setFillColor(sf::Color::White);
	this->countdownText.setString("Next wave start in " + std::to_string(this->countdown));

}

void GameState::initTowerAreas()
{
	//1
	this->towerAreas.push_back(new TowerArea(821.f, 930.f, 60.f));
	//2
	this->towerAreas.push_back(new TowerArea(660.f, 600.f, 60.f));
	//3
	this->towerAreas.push_back(new TowerArea(965.f, 590.f, 60.f));
	//4
	this->towerAreas.push_back(new TowerArea(1385.f, 590.f, 60.f));
	//5
	this->towerAreas.push_back(new TowerArea(820.f, 255.f, 60.f));
	//6
	this->towerAreas.push_back(new TowerArea(1115.f, 250.f, 60.f));
	//7
	this->towerAreas.push_back(new TowerArea(1415.f, 250.f, 60.f));
}

void GameState::spawnMonsters()
{
	if (this->isWaveStarted && !this->isCountdown &&
		this->totalMonstersAtLevelN > this->totalMonstersAtCurrentTime &&
		this->spawnTimer.getElapsedTime().asSeconds() >= 1) {
		this->spawnTimer.restart();
	
		if (this->level < 5) {
			
			this->monstersAtLevelN.push_back(new MonsterNormal(-4.f, 580.f, Entity::EntityAttributes::NORMAL, 100, 100.f, 10, this->textures["MONSTER_NORMAL_SHEET"]));
		}
		else if (this->level >= 5 && this->level < 10) {
			float randNum = float(std::rand()) / float(RAND_MAX);
			int randomAttribute = ((randNum >= 0.35f) ? 1:2) ;
			switch (randomAttribute) {
			case 1:
				this->monstersAtLevelN.push_back(new MonsterNormal(-4.f, 580.f, Entity::EntityAttributes::NORMAL, 100, 100.f, 10, this->textures["MONSTER_NORMAL_SHEET"]));
				break;
			case 2:
				this->monstersAtLevelN.push_back(new MonsterFly(-4.f, 580.f, Entity::EntityAttributes::FLY, 100, 100.f, 10, this->textures["MONSTER_FLY_SHEET"]));
				break;
			}
		}
		else if (this->level >= 10) {
			float randNum = float(std::rand() / float(RAND_MAX));

			int randomAttribute = 1;
			if (randNum < 0.6) {
				randomAttribute = 1;
			} else if (randNum < 0.9) {
				randomAttribute = 2;
			}
			else {
				randomAttribute = 3;
			}

			switch (randomAttribute) {
			case 1:
				this->monstersAtLevelN.push_back(new MonsterNormal(-4.f, 580.f, Entity::EntityAttributes::NORMAL, 100, 100.f, 10, this->textures["MONSTER_NORMAL_SHEET"]));
				break;
			case 2:
				this->monstersAtLevelN.push_back(new MonsterFly(-4.f, 580.f, Entity::EntityAttributes::FLY, 100, 100.f, 10, this->textures["MONSTER_FLY_SHEET"]));
				break;
			case 3:
				this->monstersAtLevelN.push_back(new MonsterHeavy(-4.f, 550.f, Entity::EntityAttributes::HEAVY, 100, 100.f, 10, this->textures["MONSTER_HEAVY_SHEET"]));
				break;
			}
		}

		this->totalMonstersAtCurrentTime += 1;
	}
		

}

void GameState::startLevel()
{
}



// Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::string player_name)
	: State(window, supportedKeys, states)
{

	std::srand((unsigned)std::time(NULL));

	this->playerName = player_name;
	this->initKeybinds();
	this->initTextures();

	this->texture.loadFromFile("public/bg-game.png");
	this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->bg.setTexture(&texture);

	this->initFont();
	this->initPlayer();
	this->initCreator();
	this->initButtons();
	this->initScore();

	//delete later
	this->mon_walk = false;


	this->initCountdown();
	this->initLevel();
	this->initTowerAreas();

	this->initPausedButtons();
	this->initPausedMenu();

	this->initEndButtons();
	this->initEndMenu();

	this->isGamePause = false;
	this->status = GameState::Status::PLAY;


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

	auto it2 = this->buttons.begin();
	for (it2 = this->buttons.begin(); it2 != this->buttons.end(); ++it2)
	{
		delete it2->second;
	}

	for (auto& area : this->towerAreas) {
		delete area;
	}
	this->towerAreas.clear();

	auto it3 = this->pausedButtons.begin();
	for (it3 = this->pausedButtons.begin(); it3 != this->pausedButtons.end(); ++it3) {
		delete it3->second;
	}

	auto it4 = this->endButtons.begin();
	for (it4 = this->endButtons.begin(); it4 != this->endButtons.end(); ++it4) {
		delete it4->second;
	}

	delete this->towerSeller;

	delete this->towerUpgrader;
}

void GameState::checkAndCreateTower()
{
	for (auto area : this->towerAreas) {
		if (this->selectedTowerCreator != TowerCreator::TowerType::NONE && area->isPressed(this->mousePosView) && !area->isTowerCreated()) {
			sf::Vector2f pos = area->getOriginPoint();

			area->updateIsCreated(true);
			switch (this->selectedTowerCreator) {
			case TowerCreator::TowerType::NORMAL:
				this->towersAtCurrentState.push_back(new TowerNormal(pos.x, pos.y, Entity::EntityAttributes::NORMAL, 10, 10, this->textures));
				this->selectedTowerCreator = TowerCreator::TowerType::NONE;
				break;
			case TowerCreator::TowerType::FLY:
				this->towersAtCurrentState.push_back(new TowerFly(pos.x, pos.y, Entity::EntityAttributes::FLY, 10, 10, this->textures));
				this->selectedTowerCreator = TowerCreator::TowerType::NONE;
				break;
			case TowerCreator::TowerType::HEAVY:
				this->towersAtCurrentState.push_back(new TowerHeavy(pos.x, pos.y, Entity::EntityAttributes::HEAVY, 10, 10, this->textures));
				this->selectedTowerCreator = TowerCreator::TowerType::NONE;
				break;
			default:
				std::cout << "NONE" << std::endl;
			}
		}
	}
}

bool GameState::isMonsterInTowerRadius(Tower* tower, Monster* monster)
{
	if (!monster) return false;
	sf::Vector2f towerPosition = tower->radiusShape.getPosition();
	sf::Vector2f monsterPosition = monster->getHitboxComponent()->getHitbox().getPosition();
	sf::FloatRect towerRadiusShape = tower->radiusShape.getGlobalBounds();
	sf::FloatRect monsterHitboxShape = monster->getHitboxComponent()->getHitbox().getGlobalBounds();

	float dx = (towerPosition.x + (towerRadiusShape.width / 2)) - (monsterPosition.x + (monsterHitboxShape.width / 2));
	float dy = (towerPosition.y + (towerRadiusShape.height / 2)) - (monsterPosition.y + (monsterHitboxShape.height / 2));
	float distance = std::sqrt((dx * dx) + (dy * dy));

	if (distance <= (towerRadiusShape.width / 2) + (monsterHitboxShape.width / 2))
	{
		return true;
	}
	else {
		return false;
	}
}

void GameState::checkMonstersInTowersRadius()
{
	for (auto& tower : this->towersAtCurrentState) {
		for (auto& monster : this->monstersAtLevelN) {
			
			if (
				tower->attribute == monster->attribute && 
				isMonsterInTowerRadius(tower, monster) &&
				!tower->isAlreadyDetected(monster)
				) {
				//std::cout << tower->radiusShape.getGlobalBounds(). << std::endl;
				//std::cout << tower->radiusShape.getGlobalBounds().height << std::endl;
				tower->monstersInRadius.push_back(monster);
				// delete later
				std::cout << "Detected In\n";
				//tower->monstersInRadius.erase(tower->monstersInRadius.begin());
			}
		}
	}
}

void GameState::checkMonstersOutTowersRadius()
{
	for (auto& tower : this->towersAtCurrentState) {
		for (int i = 0; i < tower->monstersInRadius.size();) {
			Monster* monster = tower->monstersInRadius[i];
			if (!isMonsterInTowerRadius(tower, monster)) {
				std::cout << "Detected Out\n";
				tower->monstersInRadius.erase(tower->monstersInRadius.begin() + i);
			}
			else {
				++i;
			}
		}
	}
}

void GameState::checkMonstersDead()
{
	//update bullet to isCollide
	for (auto& bullet : this->bulletsAtCurrentTime) {
		if (bullet->getTarget() == nullptr) {
			goto skip;
		}
		if (bullet->getTarget()->isDead) {
			skip:
			bullet->isCollide = true;
		}
	}
}

void GameState::attackMonsters()
{
	for (auto& tower : this->towersAtCurrentState) {
		//std::cout << !tower->monstersInRadius.empty() << std::endl;
		if (!tower->monstersInRadius.empty() && tower->canAttack()) {
			this->updateAttackMonsters(tower, this->selectNotDeadMonster(tower));
		}
	}
}

void GameState::monsterBulletCollision()
{
	for (auto& bullet : this->bulletsAtCurrentTime) {
	//	std::cout << bullet->getTarget() << " bulleet target \n";
		if (bullet->getHitboxComponent()->getHitbox().getGlobalBounds()
			.intersects(bullet->getTarget()->getHitboxComponent()->getHitbox().getGlobalBounds())) {
			bullet->isCollide = true;
			bullet->getTarget()->health -= bullet->damage; //********//
		}
	}
}

Monster* GameState::selectNotDeadMonster(Tower* tower)
{
	for (auto& monster : tower->monstersInRadius) {
		if (!monster->isDead) return monster;
	}
	return nullptr;
}

void GameState::checkLoseHealth()
{
	if (!this->monstersAtLevelN.empty()) {
		for (auto monster : this->monstersAtLevelN) {
			if (monster->getPosition().x > 1750) {
				monster->isDead = true;
				this->playerHealth -= 10;
				this->score -= 100;
				this->money -= 50;
			}
		}
	}

	
}

void GameState::nextLevel()
{

	this->totalMonstersAtLevelN += 5;
	this->totalMonstersAtCurrentTime = 0;
	this->spawnTimer.restart();
}

void GameState::toggleStatePaused()
{

	if (this->pauseDebounce.getElapsedTime() > sf::seconds(0.2f)) {
		this->pauseDebounce.restart(); 
		
		this->isGamePause = !this->isGamePause;

		if (this->isGamePause) {
			if (this->playerHealth > 0) {
				this->status = GameState::Status::PAUSE;
			}
			else {
				this->scoreEndText.setString(std::to_string(this->score));
				this->status = GameState::Status::END;
			}
		}
		else if (!this->isGamePause) {
			this->status = GameState::Status::PLAY;
		}

		this->countdownTimer.restart();
		
	}
}

void GameState::checkEndGame()
{
	if (this->playerHealth <= 0) {
		this->playerHealth = 0;

		this->endGame();
	}
}

void GameState::endGame()
{
	this->status = GameState::Status::END;
	this->toggleStatePaused();
	this->updateAndSaveScore();

	// sort - update - save score
}

void GameState::updateFreeAreas()
{
	if (!this->towersAtCurrentState.empty()) {
		for (auto area : this->towerAreas) {
			for (auto tower : this->towersAtCurrentState) {
				if (tower->getHitboxComponent()->getHitbox().getGlobalBounds().intersects(area->getGlobalBound())) {
					area->updateIsCreated(true);
					break;
				}
				area->updateIsCreated(false);
			}

		}
	}
}

void GameState::updateLevel()
{
	this->textLevel.setString("Level " + std::to_string(this->level));
}

void GameState::updateEndLevel()
{
	if (this->isWaveStarted && this->monstersAtLevelN.empty() && this->countdownTimer.getElapsedTime().asSeconds() > 5) {
		this->countdownTimer.restart();
		this->isCountdown = true;
		this->isWaveStarted = false;
	}
}

void GameState::updateCountdown()
{
	if (this->isCountdown && this->countdownTimer.getElapsedTime().asSeconds() >= 1) {
		if (this->countdown <= 0) {
			this->countdownTimer.restart();
			this->spawnTimer.restart();
			this->isCountdown = false;
			this->isWaveStarted = true;
			this->countdown = 30;
			this->level += 1;
			if (this->level > 1) {
				this->nextLevel();
			}
		}
		this->countdown -= 1;
		this->countdownTimer.restart();
		this->countdownText.setString("Next wave start in " + std::to_string(this->countdown));
	}
}

void GameState::updateTowersAndMonstersInteraction()
{
	if (!this->towersAtCurrentState.empty()) {
		this->checkMonstersInTowersRadius();
		this->checkMonstersOutTowersRadius();
	}
	
}

void GameState::updateSelectTower()
{
	for (int i = 0; i < this->towersAtCurrentState.size(); i++) {
		//std::cout << this->selectedTower << std::endl;

		Tower* tower = this->towersAtCurrentState[i];
		if (tower->isPressed(this->mousePosView)) {
			this->selectedTower = ((this->selectedTower == -1 || this->selectedTower != i) ? i : -1);
			this->selectedTowerCreator = TowerCreator::TowerType::NONE;
			std::cout << "Selected Tower ID : " << this->selectedTower << std::endl;
		}
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

	this->checkAndCreateTower();
}

void GameState::updateTowerSeller()
{
	if (this->towerSeller->isPressed(this->mousePosView)) {
		this->towerSeller->sellTower(this->selectedTower, &this->money, &this->towersAtCurrentState);
		this->selectedTower = -1;
	}
}

void GameState::updateTowerUpgrader()
{
	if (this->towerUpgrader->isPressed(this->mousePosView)) {
		this->towerUpgrader->upgraderTower(this->selectedTower, &this->money, &this->towersAtCurrentState);
	}
}

void GameState::updateMonstersMove(const float& dt)
{  
	if (!this->monstersAtLevelN.empty() && 1) {
		/*if (this->monstersAtLevelN[0]->getHitboxComponent()->getHitbox().getPosition().x < 1500 && !mon_walk) {
			this->monstersAtLevelN[0]->move(1.f, 0.f, dt);
		}
		else {
			this->mon_walk = true;
			this->monstersAtLevelN[0]->move(-1.f, 0.f, dt);
			if (this->monstersAtLevelN[0]->getHitboxComponent()->getHitbox().getPosition().x < 100) {
				this->mon_walk = false;
			}
		}*/

		/*for (auto& monster : this->monstersAtLevelN) {
			monster->getHitboxComponent()->update(dt, this->monstersAtLevelN[0]->getPosition());
		}*/

		if (!this->monstersAtLevelN.empty()) {
			for (auto monster : this->monstersAtLevelN) {
				monster->updateMonsterMove(dt);

				this->updateMonsterHitbox(monster);
			}
		}
	}
}

void GameState::updateMonsterHitbox(Monster* monster)
{
	monster->getHitboxComponent()->update(monster->getPosition(), monster->adjustParamHitbox.x, monster->adjustParamHitbox.y);
}

void GameState::updateMonstersDead()
{
	for (auto& monster : this->monstersAtLevelN) {
		if (monster->health <= 0) {
			monster->isDead = true;
		}
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
void GameState::updateAttackMonsters(Tower* tower, Monster* monster)
{
		this->bulletsAtCurrentTime.push_back(
			new Bullet(float(tower->getPosition().x), float(tower->getPosition().y),
				tower->attribute, tower->level, tower->damage, monster, this->textures));

}

void GameState::updateBullets(const float& dt)
{
	for (auto& bullet : this->bulletsAtCurrentTime) {
		//std::cout << "TEST\n";
		if (bullet->getTarget() != nullptr) {
			float targetX = bullet->getTarget()->getHitboxComponent()->getHitbox().getPosition().x;
			float targetY = bullet->getTarget()->getHitboxComponent()->getHitbox().getPosition().y;
			float bulletX = bullet->getHitboxComponent()->getHitbox().getPosition().x;
			float bulletY = bullet->getHitboxComponent()->getHitbox().getPosition().y;
			float dx = targetX - bulletX;
			float dy = targetY - bulletY;
		//	std::cout << dx << dy << "\n";
			bullet->getSprite()->move(sf::Vector2f(dx, dy) * (dt + 0.07f));   
			//bullet->update(dt, std::atan(dx/dy));
			bullet->getHitboxComponent()->update(bullet->getPosition(), -20.f, -20.f);
		}
	}
}

void GameState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// New game
	if (this->buttons["TOGGLE_HITBOX"]->isPressed())
	{
		this->toggleHitbox = !this->toggleHitbox;
	}
}

void GameState::updateGold()
{
	this->gold.setString("GOLD : "+std::to_string(this->money));
}

void GameState::updateScore()
{
	this->textScore.setString(std::to_string(this->score));
}

void GameState::updatePlayerHealth()
{
	if (this->playerHealth > 100) this->playerHealth = 100;
	this->textPlayerHealth.setString(std::to_string(this->playerHealth) + "/100");
}

void GameState::updatePausedMenu()
{
	for (auto button : this->pausedButtons) {
		button.second->update(this->mousePosView);
	}

	// if pressed
	if (this->pausedButtons["RESUME"]->isPressed()) {
		this->toggleStatePaused();
	}

	if (this->pausedButtons["BACK_TO_MENU"]->isPressed()) {
		this->endState();
	}
}

void GameState::updateEndMenu()
{
	for (auto button : this->endButtons) {
		button.second->update(this->mousePosView);
	}

	if (this->score < 0) this->score = 0;
	this->scoreEndText.setString(std::to_string(this->score));
	this->scoreEndText.setPosition(this->window->getSize().x / 2 - this->scoreEndText.getGlobalBounds().width / 2, 450.f);

	if (this->endButtons["BACK_TO_MENU"]->isPressed()) {
		this->endState();
	}
}

void GameState::updateAndSaveScore()
{

	typedef struct NameWithScore{
		std::string name;
		int score;
	} NameWithScore;

	auto compareScores = [](NameWithScore p_1, NameWithScore p_2) {
		return p_1.score > p_2.score;
	};

	std::vector<NameWithScore> namesWithScore;

	NameWithScore currentPlayer;
	currentPlayer.name = this->playerName;
	currentPlayer.score = this->score;

	namesWithScore.push_back(currentPlayer);
	
	std::ifstream ifs("public/scores/scores.txt");

	if (ifs.is_open())
	{
		std::string playerName = "";
		std::string playerScore = "";

		while (ifs >> playerName >> playerScore)
		{
			NameWithScore temp;
			temp.name = playerName;
			temp.score = std::stoi(playerScore);
			namesWithScore.push_back(temp);
		}


	}

	ifs.close();

	std::sort(namesWithScore.begin(), namesWithScore.end(), compareScores);

	while (namesWithScore.size() > 5) {
		namesWithScore.pop_back();
	}

	std::fstream ofs;

	ofs.open("public/scores/scores.txt", std::ios::out | std::ios::trunc);

	for (auto nameWithScore : namesWithScore) {
		ofs << nameWithScore.name + "\t" + std::to_string(nameWithScore.score) + "\n";
	}

	ofs.close();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();

	if (!isGamePause && this->status == GameState::Status::PLAY) {
		this->spawnMonsters();		
		this->updateInput(dt);
		this->updateMonstersMove(dt);

		this->player->update(dt);

		// tower creator
		for (auto& it : this->towerCreator)
		{
			it.second->update(this->mousePosView, dt);
		}

		this->updateTowerCreator(dt);
		this->updateTowerSeller();
		this->updateTowerUpgrader();

		for (auto& monster : this->monstersAtLevelN) {
			monster->update(dt);
		}

		this->updateButtons();

		//this->monstersAtLevelN->update(dt);

		// delete later
		for (auto& tower : this->towersAtCurrentState) {
			tower->update(dt);
		}

		this->updateSelectTower();

		this->updateTowersAndMonstersInteraction();

		this->checkMonstersDead();
		this->destoryMonsters();


		this->attackMonsters();
		this->checkMonstersDead();
		this->destoryMonsters();


		this->destoryBullets();
		this->updateBullets(dt);
		//	this->destoryBullets();

		this->monsterBulletCollision();
		//this->destoryBullets();

		this->updateMonstersDead();
		this->destoryMonsters();

		this->updateGold();
		this->updateScore();
		this->updatePlayerHealth();

		this->checkLoseHealth();

		this->updateCountdown();
		this->updateEndLevel();
		this->updateLevel();
		this->updateFreeAreas();

		this->checkEndGame();
	
	}

	else if (this->isGamePause && this->status == GameState::Status::PAUSE) {
		this->updatePausedMenu();

		// change later
	
	}

	else if (this->isGamePause && this->status == GameState::Status::END &&
		this->status != GameState::Status::PAUSE) {
		this->updateEndMenu();
	}
}

void GameState::destoryBullets()
{
	for (int i = 0; i < this->bulletsAtCurrentTime.size();) {
		if (this->bulletsAtCurrentTime[i]->isCollide) {
			delete this->bulletsAtCurrentTime[i];
			this->bulletsAtCurrentTime.erase(this->bulletsAtCurrentTime.begin() + i);
		}
		else {
			++i;
		}
		//std::cout << "BULL SIZE: " << this->bulletsAtCurrentTime.size() << "\n";
	}
}

void GameState::destoryMonsters()
{
	for (int i = 0; i < this->monstersAtLevelN.size();) {
		if (this->monstersAtLevelN[i]->isDead) {
			//delete this->monstersAtLevelN[i];
			this->score += 100;
			this->money += 50;
			this->monstersAtLevelN.erase(this->monstersAtLevelN.begin() + i);
		}
		else {
			++i;
		}
	}
}

void GameState::renderPausedMenu(sf::RenderTarget* target)
{
	target->draw(this->pausedPlane);


	for (auto button : this->pausedButtons) {
		button.second->render(target);
	}
}

void GameState::renderEndMenu(sf::RenderTarget* target)
{
	target->draw(this->endPlane);

	target->draw(this->endText);
	target->draw(this->scoreEndText);

	for (auto button : this->endButtons) {
		button.second->render(target);
	}
}

void GameState::renderTowerAreas(sf::RenderTarget* target)
{
	if (this->toggleHitbox) {
		for (auto area : this->towerAreas) {
			area->render(target);
		}
	}
}

void GameState::renderLevel(sf::RenderTarget* target)
{
	target->draw(this->textLevel);
}

void GameState::renderCountdown(sf::RenderTarget* target)
{
	if (this->isCountdown) {
		target->draw(this->countdownText);
	}
}

void GameState::renderTowerCreators(sf::RenderTarget* target)
{
	for (auto& it : this->towerCreator)
	{
		it.second->render(target);
	}
}

void GameState::renderTowerSeller(sf::RenderTarget* target)
{
	if (this->selectedTower != -1) {
		this->towerSeller->render(target);
	}
}

void GameState::renderTowerUpgrader(sf::RenderTarget* target)
{
	if (this->selectedTower != -1 && this->towersAtCurrentState[this->selectedTower]->level < 3) {
		this->towerUpgrader->render(target);
	}
}

void GameState::renderTowers(sf::RenderTarget* target)
{
	//this->monstersAtLevelN->render(target);
	if (!this->towersAtCurrentState.empty()) {
		for (auto& tower : this->towersAtCurrentState) {
			tower->render(target);
			if (tower->radius != 0.f && this->toggleHitbox) {
				target->draw(tower->radiusShape);
				target->draw(tower->getHitboxComponent()->getHitbox());
			}
		}
	}
}

void GameState::renderMonsters(sf::RenderTarget* target)
{
	if (!this->monstersAtLevelN.empty()) {
		for (auto& monster : this->monstersAtLevelN) {
			if (!monster->isDead) {
				monster->render(target);
				if (monster->getHitboxComponent() != nullptr && this->toggleHitbox) {
					target->draw(monster->getHitboxComponent()->getHitbox());
				}
			}
			
		}
	}
}

void GameState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		//std::cout << it.second->isPressed() << "\n";
		it.second->render(target);
	}
}

void GameState::renderBullet(sf::RenderTarget* target)
{
	for (auto& bullet : this->bulletsAtCurrentTime) {
		if (!bullet->isCollide) {
			bullet->render(target);
			if (bullet->getHitboxComponent() != nullptr && this->toggleHitbox) {
				target->draw(bullet->getHitboxComponent()->getHitbox());
			}
		}
	}

}

void GameState::renderGold(sf::RenderTarget* target)
{
	target->draw(this->gold);
}

void GameState::renderScore(sf::RenderTarget* target)
{
	target->draw(this->textScore);
}

void GameState::renderPlayerHealth(sf::RenderTarget* target)
{
	target->draw(this->textPlayerHealth);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->bg);

	this->player->render(target);
	target->draw(this->textName);

	this->renderTowerCreators(target);
	this->renderTowerSeller(target);
	this->renderTowerUpgrader(target);

	this->renderButtons(target);

	this->renderTowers(target);

	this->renderMonsters(target);
	this->renderBullet(target);

	this->renderGold(target);
	this->renderScore(target);
	this->renderPlayerHealth(target);

	this->renderCountdown(target);
	this->renderLevel(target);
	this->renderTowerAreas(target);

	if (this->status == GameState::Status::PAUSE) {
		this->renderPausedMenu(target);

		// change later 

	
	}
	else if (this->status == GameState::Status::END &&
		this->status != GameState::Status::PAUSE) {
		this->renderEndMenu(target);
	}

	// remove later
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(18);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}
