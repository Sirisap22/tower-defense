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

class GameState :
    public State
{
private:
    Player* player;
    std::vector<Monster*> monstersAtLevelN;
    std::vector<Tower*> towersAtCurrentState;
    sf::Texture texture;
    sf::RectangleShape bg;
    int level;


    // Functions
    void initKeybinds();
    void initTextures();
    void initPlayer();
    void initLevel();
    void incrementLevel();
    void startLevel();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    // Functions

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

#endif
