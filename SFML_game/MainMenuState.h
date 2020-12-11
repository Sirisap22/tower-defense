#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"
//#include "Plane.h"
#include "InputFieldPlane.h"
#include "InputField.h"
#include "CreditPlane.h"

class MainMenuState :
    public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    bool toggleLeaderBoard;
    bool toggleInputField;
    bool toggleCreditPlane;
    bool* shouldPollEvent;
    sf::Event event;

    std::map<std::string, Button*> buttons;
    Plane* leaderBoard;
    InputFieldPlane* InputPlane;
    InputField* input;
    CreditPlane* creditPlane;

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    void initLeaderBoard();
    void initInputField();
    void initCreditPlane();

 public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, bool* shouldPollEvent);
    virtual ~MainMenuState();

    // Functions

    void toggleStatePaused();
    void updateInput(const float& dt);
    void updateShouldPollEvent();
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);
};
#endif

