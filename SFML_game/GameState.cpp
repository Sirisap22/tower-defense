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
	if (!this->font.loadFromFile("Fonts/Play-Regular.ttf")) {
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
	this->level = 1;
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
	
	// init normal monsters
	for (int i = 0; i < 2; ++i) {
		this->monstersAtLevelN.push_back(new MonsterNormal(-4.f, 580.f, Entity::EntityAttributes::NORMAL, 100, 100.f, 10, this->textures["MONSTER_NORMAL_SHEET"]));
	}

	// init heavy monsters
	//for (int i = 0; i < 1; ++i) {
	//	this->monstersAtLevelN.push_back(new MonsterHeavy(100, 100, Entity::EntityAttributes::HEAVY, 100, 100.f, 10, this->textures["MONSTER_HEAVY_SHEET"]));
	//}

	// init fly monsters
	//for (int i = 0; i < 2; ++i) {
	//	this->monstersAtLevelN.push_back(new MonsterFly(100 * 2 * (i + 1), 100 * 2 * (i + 1), Entity::EntityAttributes::FLY, 100, 100.f, 10, this->textures["MONSTER_FLY_SHEET"]));
	//}

	

}

void GameState::incrementLevel()
{

}

void GameState::startLevel()
{
}



// Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::string player_name)
	: State(window, supportedKeys, states)
{

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

	auto it2 = this->buttons.begin();
	for (it2 = this->buttons.begin(); it2 != this->buttons.end(); ++it2)
	{
		delete it2->second;
	}

	delete this->towerSeller;

	delete this->towerUpgrader;
}

void GameState::checkAndCreateTower()
{
	if (this->selectedTowerCreator != TowerCreator::TowerType::NONE && this->mousePosView.y < 800 && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		switch (this->selectedTowerCreator) {
		case TowerCreator::TowerType::NORMAL:
			this->towersAtCurrentState.push_back(new TowerNormal(this->mousePosView.x, this->mousePosView.y, Entity::EntityAttributes::NORMAL, 10, 10, this->textures));
			this->selectedTowerCreator = TowerCreator::TowerType::NONE;
			break;
		case TowerCreator::TowerType::FLY:
			this->towersAtCurrentState.push_back(new TowerFly(this->mousePosView.x, this->mousePosView.y, Entity::EntityAttributes::FLY, 10, 10, this->textures));
			this->selectedTowerCreator = TowerCreator::TowerType::NONE;
			break;
		case TowerCreator::TowerType::HEAVY:
			this->towersAtCurrentState.push_back(new TowerHeavy(this->mousePosView.x, this->mousePosView.y, Entity::EntityAttributes::HEAVY, 10, 10, this->textures));
			this->selectedTowerCreator = TowerCreator::TowerType::NONE;
			break;
		default:
			std::cout << "NONE" << std::endl;
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
	if (!this->monstersAtLevelN.empty()) {
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

		this->monstersAtLevelN[0]->updateMonsterMove(dt);

		this->updateMonsterHitbox(this->monstersAtLevelN[0]);
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

void GameState::update(const float& dt)
{
	this->updateMousePositions();
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
			this->monstersAtLevelN.erase(this->monstersAtLevelN.begin() + i);
		}
		else {
			++i;
		}
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

	// remove later
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y-50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(18);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}
