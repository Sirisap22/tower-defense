#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Monster.h"
#include "MonsterNormal.h"
#include "MonsterHeavy.h"
#include "MonsterFly.h"
#include "Tower.h"
#include "TowerNormal.h"
#include "TowerFly.h"
#include "TowerHeavy.h"
#include "TowerCreator.h"
#include "Button.h"
#include "TowerSeller.h"
#include "TowerUpgrader.h"

class GameState :
    public State
{
private:
    Player* player;
    std::vector<Monster*> monstersAtLevelN;
    std::vector<Tower*> towersAtCurrentState;
    std::vector<Bullet* > bulletsAtCurrentTime;
    sf::Texture texture;
    sf::RectangleShape bg;
    std::map<std::string, TowerCreator*> towerCreator;
    TowerSeller* towerSeller;
    TowerUpgrader* towerUpgrader;
    TowerCreator::TowerType selectedTowerCreator;
    int selectedTower;
    std::map<std::string, Button*> buttons;
    sf::Font font;
    bool toggleHitbox;
    int level;
    sf::Text textLevel;
    int playerHealth;
    sf::Text textPlayerHealth;
    int money;
    sf::Text gold;
    int score;
    sf::Text textScore;
    std::string playerName;
    sf::Text textName;
    

    // delete later 
    bool mon_walk;

    // Functions
    void initKeybinds();
    void initTextures();
    void initCreator();
    void initPlayer();
    void initFont();
    void initButtons();
    void initScore();
    void initLevel();
    void incrementLevel();
    void startLevel();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::string player_name);
    virtual ~GameState();

    // Functions

    void checkAndCreateTower();
    bool isMonsterInTowerRadius(Tower* tower, Monster* monster);
    void checkMonstersInTowersRadius();
    void checkMonstersOutTowersRadius();

    void checkMonstersDead();
    void attackMonsters();
    void monsterBulletCollision();
    Monster* selectNotDeadMonster(Tower* tower);
    void checkLoseHealth();

    
    void updateTowersAndMonstersInteraction();
    void updateSelectTower();
    void updateTowerCreator(const float& dt);
    void updateTowerSeller();
    void updateTowerUpgrader();
    void updateMonstersMove(const float& dt);
    void updateMonsterHitbox(Monster* monster);
    void updateMonstersDead();
    void updateInput(const float& dt);
    void updateAttackMonsters(Tower* tower, Monster* monster);
    void updateBullets(const float& dt);
    void updateButtons();
    void updateGold();
    void updateScore();
    void updatePlayerHealth();
    void update(const float& dt);

    void destoryBullets();
    void destoryMonsters();

    void renderTowerCreators(sf::RenderTarget* target);
    void renderTowerSeller(sf::RenderTarget* target);
    void renderTowerUpgrader(sf::RenderTarget* target);
    void renderTowers(sf::RenderTarget* target);
    void renderMonsters(sf::RenderTarget* target);
    void renderButtons(sf::RenderTarget* target);
    void renderBullet(sf::RenderTarget* target);
    void renderGold(sf::RenderTarget* target);
    void renderScore(sf::RenderTarget* target);
    void renderPlayerHealth(sf::RenderTarget* target);
    void render(sf::RenderTarget* target = NULL);
};

#endif
