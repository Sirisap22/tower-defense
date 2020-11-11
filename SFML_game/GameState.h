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

class GameState :
    public State
{
//enum TowerType { NORMAL = 0, FLY, HEAVY };
private:
    Player* player;
    std::vector<Monster*> monstersAtLevelN;
    std::vector<Tower*> towersAtCurrentState;
    std::vector<Bullet* > bulletsAtCurrentTime;
    sf::Texture texture;
    sf::RectangleShape bg;
    std::map<std::string, TowerCreator*> towerCreator;
    TowerCreator::TowerType selectedTowerCreator;
    std::map<std::string, Button*> buttons;
    sf::Font font;
    bool toggleHitbox;
    int level;
    int playerHealth;
    int money;

    // delete later 
    bool mon_walk;

    // Functions
    void initKeybinds();
    void initTextures();
    void initCreator();
    void initPlayer();
    void initFont();
    void initButtons();
    void initLevel();
    void incrementLevel();
    void startLevel();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    // Functions

    void checkAndCreateTower();
    bool isMonsterInTowerRadius(Tower* tower, Monster* monster);
    void checkMonstersInTowersRadius();
    void checkMonstersOutTowersRadius();
    
    void updateTowersAndMonstersInteraction();
    void updateTowerCreator(const float& dt);
    void updateMonstersMove(const float& dt);
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);

    void renderTowerCreators(sf::RenderTarget* target);
    void renderTowers(sf::RenderTarget* target);
    void renderMonsters(sf::RenderTarget* target);
    void renderButtons(sf::RenderTarget* target);
    void render(sf::RenderTarget* target = NULL);
};

#endif
