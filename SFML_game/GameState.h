#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
class GameState :
    public State
{
private:
    Player* player;
    Monster* monstersAtLevelN;
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
