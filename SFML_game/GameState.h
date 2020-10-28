#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
class GameState :
    public State
{
private:
    Player* player;
    MonsterNormal* monsters_normal;
    sf::Texture texture;
    sf::RectangleShape bg;

    // Functions
    void initKeybinds();
    void initTextures();
    void initEntities();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    // Functions

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

#endif
