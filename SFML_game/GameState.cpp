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
	this->towerCreator["NORMAL"] = new TowerCreator(1340.f, 825.f, 100.f, 250.f, TowerCreator::TowerType::NORMAL, this->textures["TOWER_CREATOR_NORMAL"]);
	this->towerCreator["FLY"] = new TowerCreator(1540.f, 825.f, 100.f, 250.f, TowerCreator::TowerType::FLY, this->textures["TOWER_CREATOR_FLY"]);
	this->towerCreator["HEAVY"] = new TowerCreator(1740.f, 825.f, 100.f, 250.f, TowerCreator::TowerType::HEAVY, this->textures["TOWER_CREATOR_HEAVY"]);
}

void GameState::initPlayer()
{
	sf::Text player;
	player.setString(this->playerName);
	player.setPosition(10.f, 10.f);
	player.setCharacterSize(48);
	player.setOutlineColor(sf::Color::Black);
	player.setOutlineThickness(1.f);
	player.setFont(this->font);
	player.setFillColor(sf::Color::White);
	this->textName = player;

	this->playerHealth = 100;
	sf::Text health;
	this->hpOutline.setSize(sf::Vector2f(this->playerHealth * 5.f, 40.f));
	this->hpOutline.setOutlineThickness(1.f);
	this->hpOutline.setOutlineColor(sf::Color::Black);
	this->hpOutline.setFillColor(sf::Color::Red);
	this->hpOutline.setPosition(10.f + player.getGlobalBounds().width + 10.f, 20.f);

	this->hp.setSize(sf::Vector2f(this->playerHealth * 5.f, 40.f));
	this->hp.setFillColor(sf::Color::Green);
	this->hp.setPosition(10.f + player.getGlobalBounds().width + 10.f, 20.f);

	this->money = 500;
	
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
		1080.f, 910.f, 200.f, 50.f,
		&this->font, "Toggle Hitbox", 24,
		sf::Color(250, 250, 250, 250), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 0)
	);

	this->buttons["START_WAVE"] = new Button(
		1080.f, 860.f, 200.f, 50.f,
		&this->font, "Start Wave", 24,
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

	this->pausedButtons["END_GAME"] = new Button(
		300.f, 500.f, 200.f, 50.f,
		&this->font, "End Game", 72,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 100), sf::Color(70, 70, 70, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->pausedButtons["BACK_TO_MENU"] = new Button(
		300.f, 600.f, 200.f, 50.f,
		&this->font, "Back To Menu", 72,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 100), sf::Color(70, 70, 70, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void GameState::initPausedMenu()
{
	this->pausedPlane.setFillColor(sf::Color(70, 70, 70, 200));
	this->pausedPlane.setPosition(180.f, 0.f);
	this->pausedPlane.setSize(sf::Vector2f(440.f, (float)this->window->getSize().y));

}

void GameState::initEndButtons()
{
	this->endButtons["BACK_TO_MENU"] = new Button(
		this->window->getSize().x/2, 570.f, 400.f, 100.f,
		&this->font, "Back To Menu", 72,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 100), sf::Color(70, 70, 70, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->endButtons["BACK_TO_MENU"]->setButtonPosition(this->window->getSize().x / 2 - this->endButtons["BACK_TO_MENU"]->getTextGlobalBounds().width / 2, 570.f);    void setButtonPosition();
	this->endButtons["BACK_TO_MENU"]->setShapePosition(this->window->getSize().x / 2 - this->endButtons["BACK_TO_MENU"]->getTextGlobalBounds().width / 2, 570.f);    void setButtonPosition();

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
	this->endText.setOutlineColor(sf::Color::Black);
	this->endText.setOutlineThickness(1.f);

	this->scoreEndText.setFont(this->font);
	this->scoreEndText.setCharacterSize(72);
	this->scoreEndText.setFillColor(sf::Color::White);
	this->scoreEndText.setPosition(this->window->getSize().x / 2 - this->scoreEndText.getGlobalBounds().width / 2, 450.f);
	this->scoreEndText.setOutlineColor(sf::Color::Black);
	this->scoreEndText.setOutlineThickness(1.f);

}

void GameState::initScore()
{
	this->score = 0;
	this->textScore.setString("Score : " + std::to_string(this->score));
	this->textScore.setCharacterSize(48);
	this->textScore.setFont(this->font);
	this->textScore.setOutlineColor(sf::Color::Black);
	this->textScore.setOutlineThickness(1.f);
	this->textScore.setFillColor(sf::Color::White);
	this->textScore.setPosition(this->window->getSize().x - 20.f - this->textScore.getGlobalBounds().width, 10.f);

}

void GameState::initLevel()
{
	this->level = 0;

	this->textLevel.setCharacterSize(48);
	this->textLevel.setFont(this->font);
	this->textLevel.setOutlineColor(sf::Color::Black);
	this->textLevel.setOutlineThickness(1.f);
	this->textLevel.setFillColor(sf::Color::White);
	this->textLevel.setString("Level "+std::to_string(this->level));
	this->textLevel.setPosition(this->window->getSize().x - 20.f - this->textLevel.getGlobalBounds().width, 10.f + this->textScore.getGlobalBounds().height + 20.f);

	this->selectedTower = -1;
	this->toggleHitbox = false;

	this->gold.setFont(this->font);
	this->gold.setString("GOLD : "+std::to_string(this->money));
	this->gold.setCharacterSize(48);
	this->gold.setOutlineColor(sf::Color::Black);
	this->gold.setOutlineThickness(1.f);
	this->gold.setPosition(sf::Vector2f(10.f, 10.f + this->textName.getGlobalBounds().height + 20.f ));
	this->gold.setFillColor(sf::Color::Yellow);

	this->towerSeller = new TowerSeller(1640.f, 620.f);
	this->towerUpgrader = new TowerUpgrader(1440.f, 620.f);
	
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
	this->countdownText.setCharacterSize(48);
	this->countdownText.setFillColor(sf::Color::White);
	this->countdownText.setString("Next wave start in " + std::to_string(this->countdown));
	this->countdownText.setOutlineThickness(1.f);
	this->countdownText.setOutlineColor(sf::Color::Black);
	this->countdownText.setPosition(10.f, 980.f);
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

void GameState::initTowerCreatorPointers()
{
	for (int i = 0; i < 3; ++i) {
		sf::CircleShape* temp = new sf::CircleShape(10, 3);
		temp->setRotation(180.f);
		temp->setFillColor(sf::Color::Green);
		temp->setOutlineThickness(3.f);
		temp->setOutlineColor(sf::Color::Black);
		temp->setPosition(1340.f + i * 200 + 171.f/2.f + temp->getGlobalBounds().width/4 , 825.f+20.f);


		this->towerCreatorPointers.push_back(temp);
	}

}

void GameState::initTowerPointer()
{
	sf::CircleShape temp = sf::CircleShape(10, 3);
	temp.setRotation(180.f);
	temp.setFillColor(sf::Color::Green);
	temp.setOutlineThickness(3.f);
	temp.setOutlineColor(sf::Color::Black);

	this->towerPointer = temp;
}

void GameState::initSounds()
{
	if (!this->clickBuffer.loadFromFile("public/sounds/click.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->click.setBuffer(this->clickBuffer);
	this->click.setVolume(50.f);

	if (!this->buildBuffer.loadFromFile("public/sounds/build_tower.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->build.setBuffer(this->buildBuffer);
	this->build.setVolume(50.f);

	if (!this->upgradeBuffer.loadFromFile("public/sounds/upgrade_tower.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->upgrade.setBuffer(this->upgradeBuffer);
	this->upgrade.setVolume(50.f);

	if (!this->sellBuffer.loadFromFile("public/sounds/sell_tower.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->sell.setBuffer(this->sellBuffer);
	this->sell.setVolume(50.f);

	if (!this->endBuffer.loadFromFile("public/sounds/end_game.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->end.setBuffer(this->endBuffer);
	this->end.setVolume(50.f);

	if (!this->towerBuffer.loadFromFile("public/sounds/tower.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->tower.setBuffer(this->towerBuffer);
	this->tower.setVolume(50.f);

	if (!this->selectBuffer.loadFromFile("public/sounds/select_click.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->select.setBuffer(this->selectBuffer);
	this->select.setVolume(50.f);

	if (!this->healthBuffer.loadFromFile("public/sounds/health.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->health.setBuffer(this->healthBuffer);
	this->health.setVolume(50.f);

	if (!this->arrowBuffer.loadFromFile("public/sounds/arrow.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->arrow.setBuffer(this->arrowBuffer);
	this->arrow.setVolume(30.f);
	
	if (!this->magicBuffer.loadFromFile("public/sounds/magic.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->magic.setBuffer(this->magicBuffer);
	this->magic.setVolume(30.f);

	if (!this->rockBuffer.loadFromFile("public/sounds/rock.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->rock.setBuffer(this->rockBuffer);
	this->rock.setVolume(30.f);

	if (!this->waveBuffer.loadFromFile("public/sounds/wave.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->wave.setBuffer(this->waveBuffer);
	this->wave.setVolume(50.f);

	if (!this->errorBuffer.loadFromFile("public/sounds/error.wav")) {
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_SOUND");
	}

	this->error.setBuffer(this->errorBuffer);
	this->error.setVolume(50.f);

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
				this->monstersAtLevelN.push_back(new MonsterFly(-4.f, 580.f, Entity::EntityAttributes::FLY, 100, 120.f, 5, this->textures["MONSTER_FLY_SHEET"]));
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
				this->monstersAtLevelN.push_back(new MonsterFly(-4.f, 580.f, Entity::EntityAttributes::FLY, 100, 120.f, 5, this->textures["MONSTER_FLY_SHEET"]));
				break;
			case 3:
				this->monstersAtLevelN.push_back(new MonsterHeavy(-4.f, 550.f, Entity::EntityAttributes::HEAVY, 100, 90.f, 20, this->textures["MONSTER_HEAVY_SHEET"]));
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
	this->initTowerCreatorPointers();
	this->initSounds();
	this->initTowerPointer();

	this->isGamePause = false;
	this->status = GameState::Status::PLAY;


}

GameState::~GameState()
{


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

	for (auto& pointer : this->towerCreatorPointers) {
		delete pointer;
	}
	this->towerCreatorPointers.clear();

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
				if (this->money - 100 < 0){
					this->error.play();
					return;
				}
				this->money -= 100;
				this->build.play();
				this->towersAtCurrentState.push_back(new TowerNormal(pos.x, pos.y, Entity::EntityAttributes::NORMAL, 10, 10, this->textures));
				this->selectedTowerCreator = TowerCreator::TowerType::NONE;
				break;
			case TowerCreator::TowerType::FLY:
				if (this->money - 150 < 0) {
					this->error.play();
					return;
				}
				this->money -= 150;
				this->build.play();
				this->towersAtCurrentState.push_back(new TowerFly(pos.x, pos.y, Entity::EntityAttributes::FLY, 10, 10, this->textures));
				this->selectedTowerCreator = TowerCreator::TowerType::NONE;
				break;
			case TowerCreator::TowerType::HEAVY:
				if (this->money - 200 < 0) {
					this->error.play();
					return;
				}
				this->build.play();
				this->money -= 200;
				this->towersAtCurrentState.push_back(new TowerHeavy(pos.x, pos.y, Entity::EntityAttributes::HEAVY, 10, 10, this->textures));
				this->selectedTowerCreator = TowerCreator::TowerType::NONE;
				break;
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
				tower->monstersInRadius.push_back(monster);
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
		if (!tower->monstersInRadius.empty() && tower->canAttack()) {
			this->updateAttackMonsters(tower, this->selectNotDeadMonster(tower));
		}
	}
}

void GameState::monsterBulletCollision()
{
	for (auto& bullet : this->bulletsAtCurrentTime) {
		if (bullet->getHitboxComponent()->getHitbox().getGlobalBounds()
			.intersects(bullet->getTarget()->getHitboxComponent()->getHitbox().getGlobalBounds())) {
			switch (bullet->getTarget()->attribute) {
			case (Entity::EntityAttributes::NORMAL):
				this->arrow.play();
				break;
			case(Entity::EntityAttributes::FLY):
				this->magic.play();
				break;
			case(Entity::EntityAttributes::HEAVY):
				this->rock.play();
				break;
			}
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
				this->health.play();
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
		else if (!this->isGamePause /*&& !this->skipToEnd*/) {
			this->status = GameState::Status::PLAY;
			/*if (this->playerHealth <= 0) {
				this->skipToEnd = true;
			}*/
		}

		this->countdownTimer.restart();
		
	}
}

void GameState::checkEndGame()
{
	if (this->playerHealth <= 0) {
		this->playerHealth = 0;
		this->hp.setSize(sf::Vector2f(this->playerHealth * 5, 40.f));
		this->score += 100;
		this->textScore.setString("Score : " + std::to_string(this->score));
		this->textScore.setPosition(this->window->getSize().x - 20.f - this->textScore.getGlobalBounds().width, 10.f);
		this->endGame();
	}
}

void GameState::endGame()
{
	this->end.play();
	this->playerHealth = 0;
	this->isGamePause = true;
	this->status = GameState::Status::END;
	this->toggleStatePaused();
	this->updateAndSaveScore();

}

void GameState::highlightSelectedTowerCreator()
{
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
	else {
		for (auto area : this->towerAreas) {
			area->updateIsCreated(false);
		}
	}
}

void GameState::updateTowerPointer()
{
	if (this->selectedTower != -1) {
		Tower* tower = this->towersAtCurrentState[this->selectedTower];
		this->towerPointer.setPosition(tower->getPosition().x + tower->getGlobalBounds().width / 2+3.f, tower->getPosition().y - 20.f);
		if (tower->attribute == Entity::EntityAttributes::HEAVY) {
			this->towerPointer.setPosition(tower->getPosition().x + tower->getGlobalBounds().width / 2, tower->getPosition().y - 20.f);
		}
	}
}

void GameState::updateLevel()
{
	this->textLevel.setString("Level " + std::to_string(this->level));
	this->textLevel.setPosition(this->window->getSize().x - 20.f - this->textLevel.getGlobalBounds().width, 10.f + this->textScore.getGlobalBounds().height + 10.f);
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
			if (this->level == 1) {
				this->wave.play();
			}
			if (this->level > 1) {
				this->wave.play();
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

		Tower* tower = this->towersAtCurrentState[i];
		if (tower->isPressed(this->mousePosView)) {
			this->tower.play();
			this->selectedTower = ((this->selectedTower == -1 || this->selectedTower != i) ? i : -1);
			this->selectedTowerCreator = TowerCreator::TowerType::NONE;
		}
	}
}

void GameState::updateTowerCreator(const float& dt)
{
	for (auto& towerCreator : this->towerCreator) {
		if (towerCreator.second->isPressed()) {
			this->select.play();
			// toggle selected item
			if (this->selectedTowerCreator == towerCreator.second->selectedTowerType() && this->selectedTowerCreator != TowerCreator::TowerType::NONE) {
				this->selectedTowerCreator = TowerCreator::TowerType::NONE;
			}
			else {
				this->selectedTowerCreator = towerCreator.second->selectedTowerType();
			}

			
		}
	}

	this->checkAndCreateTower();
}

void GameState::updateTowerSeller()
{
	if (this->towerSeller->isPressed(this->mousePosView)) {
		this->sell.play();
		this->towerSeller->sellTower(this->selectedTower, &this->money, &this->towersAtCurrentState);
		this->selectedTower = -1;
	}
}

void GameState::updateTowerUpgrader()
{
	if (this->towerUpgrader->isPressed(this->mousePosView)) {
		if (this->money - 200 < 0) {
			this->error.play();
			return;
		}
		this->upgrade.play();
		this->towerUpgrader->upgraderTower(this->selectedTower, &this->money, &this->towersAtCurrentState);
	}
}

void GameState::updateMonstersMove(const float& dt)
{  
	if (!this->monstersAtLevelN.empty()) {
	
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
	// contral input
	if (this->keyPressedClock.getElapsedTime() > sf::seconds(0.2f)) {
		this->keyPressedClock.restart();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->select.play();
			this->selectedTowerCreator = this->selectedTowerCreator == TowerCreator::TowerType::NORMAL ? TowerCreator::TowerType::NONE : TowerCreator::TowerType::NORMAL;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->select.play();
			this->selectedTowerCreator = this->selectedTowerCreator == TowerCreator::TowerType::FLY ? TowerCreator::TowerType::NONE : TowerCreator::TowerType::FLY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->select.play();
			this->selectedTowerCreator = this->selectedTowerCreator == TowerCreator::TowerType::HEAVY ? TowerCreator::TowerType::NONE : TowerCreator::TowerType::HEAVY;
		}
		else if (this->selectedTower != -1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				if (this->money - 200 < 0) return;
				this->upgrade.play();
				this->towerUpgrader->upgraderTower(this->selectedTower, &this->money, &this->towersAtCurrentState);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
				this->sell.play();
				this->towerSeller->sellTower(this->selectedTower, &this->money, &this->towersAtCurrentState);
				this->selectedTower = -1;
			}
		}
	}

}
void GameState::updateAttackMonsters(Tower* tower, Monster* monster)
{
		this->bulletsAtCurrentTime.push_back(
			new Bullet(float(tower->getPosition().x)+70.f, float(tower->getPosition().y),
				tower->attribute, tower->level, tower->damage, monster, this->textures));

}

void GameState::updateBullets(const float& dt)
{
	for (auto& bullet : this->bulletsAtCurrentTime) {
		if (bullet->getTarget() != nullptr) {
			float targetX = bullet->getTarget()->getHitboxComponent()->getHitbox().getPosition().x;
			float targetY = bullet->getTarget()->getHitboxComponent()->getHitbox().getPosition().y;
			float bulletX = bullet->getHitboxComponent()->getHitbox().getPosition().x;
			float bulletY = bullet->getHitboxComponent()->getHitbox().getPosition().y;
			float dx = targetX - bulletX;
			float dy = targetY - bulletY;
			bullet->getSprite()->move(sf::Vector2f(dx, dy) * (0.1f));   
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
		this->click.play();
		this->toggleHitbox = !this->toggleHitbox;
	}

	if (this->buttons["START_WAVE"]->isPressed() && !this->isWaveStarted) {
		this->click.play();
		this->countdown = 0;
	}

}

void GameState::updateGold()
{
	this->gold.setString("GOLD : "+std::to_string(this->money));
}

void GameState::updateScore()
{
	this->textScore.setString("Score : " + std::to_string(this->score));
	this->textScore.setPosition(this->window->getSize().x - 20.f - this->textScore.getGlobalBounds().width, 10.f);
}

void GameState::updatePlayerHealth()
{
	if (this->playerHealth > 100) this->playerHealth = 100;
	this->hp.setSize(sf::Vector2f(this->playerHealth * 5, 40.f));
}

void GameState::updatePausedMenu()
{
	for (auto button : this->pausedButtons) {
		button.second->update(this->mousePosView);
	}

	// if pressed
	if (this->pausedButtons["RESUME"]->isPressed()) {
		this->click.play();
		this->toggleStatePaused();
	}	
	
	if (this->pausedButtons["END_GAME"]->isPressed()) {
		this->click.play();
		this->score -= 100;
		this->playerHealth = 0;
		this->endGame();
	}

	if (this->pausedButtons["BACK_TO_MENU"]->isPressed()) {
		this->click.play();
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
		this->click.play();
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
		this->updateTowerPointer();
	
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

void GameState::renderTowerPointer(sf::RenderTarget* target)
{
	if (this->selectedTower != -1) {
		target->draw(this->towerPointer);
	}
}

void GameState::renderTowerCreatorPointers(sf::RenderTarget* target)
{
	switch (this->selectedTowerCreator){
	case (TowerCreator::TowerType::NORMAL):
		target->draw(*this->towerCreatorPointers[0]);
		break;
	case(TowerCreator::TowerType::FLY):
		target->draw(*this->towerCreatorPointers[1]);
		break;
	case(TowerCreator::TowerType::HEAVY):
		target->draw(*this->towerCreatorPointers[2]);
		break;
	default:
		break;
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

	this->buttons["TOGGLE_HITBOX"]->render(target);
	if (!this->isWaveStarted) {
		this->buttons["START_WAVE"]->render(target);
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
	target->draw(this->hpOutline);
	target->draw(this->hp);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->bg);

	target->draw(this->textName);

	this->renderButtons(target);

	this->renderTowers(target);

	this->renderTowerCreators(target);
	this->renderTowerSeller(target);
	this->renderTowerUpgrader(target);

	this->renderMonsters(target);
	this->renderBullet(target);

	this->renderGold(target);
	this->renderScore(target);
	this->renderPlayerHealth(target);

	this->renderCountdown(target);
	this->renderLevel(target);
	this->renderTowerAreas(target);
	this->renderTowerPointer(target);
	this->renderTowerCreatorPointers(target);

	if (this->status == GameState::Status::PAUSE) {
		this->renderPausedMenu(target);

	
	}
	else if (this->status == GameState::Status::END &&
		this->status != GameState::Status::PAUSE) {
		this->renderEndMenu(target);
	}

}
