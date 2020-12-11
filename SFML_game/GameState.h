#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstdlib>
#include <algorithm>

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
#include "TowerArea.h"

class GameState :
    public State
{
private:
    enum class Status {
        PLAY,
        PAUSE,
        END
    };
    std::vector<Monster*> monstersAtLevelN;
    std::vector<Tower*> towersAtCurrentState;
    std::vector<Bullet*> bulletsAtCurrentTime;
    std::vector<TowerArea*> towerAreas;
    std::vector<sf::CircleShape* > towerCreatorPointers;
    sf::Texture texture;
    sf::RectangleShape bg;
    std::map<std::string, TowerCreator*> towerCreator;
    TowerSeller* towerSeller;
    TowerUpgrader* towerUpgrader;
    TowerCreator::TowerType selectedTowerCreator;
    int selectedTower;
    std::map<std::string, Button*> buttons;
    std::map<std::string, Button*> pausedButtons;
    std::map<std::string, Button*> endButtons;
    sf::RectangleShape pausedPlane;
    sf::RectangleShape endPlane;
    sf::Text endText;
    sf::Text scoreEndText;
    sf::Font font;
    bool toggleHitbox;
    int level;
    sf::Text textLevel;
    int playerHealth;
    sf::Text textPlayerHealth;
    sf::RectangleShape hpOutline;
    sf::RectangleShape hp;
    int money;
    sf::Text gold;
    int score;
    sf::Text textScore;
    std::string playerName;
    sf::Text textName;
    sf::Clock spawnTimer;
    int totalMonstersAtLevelN;
    int totalMonstersAtCurrentTime;
    bool isCountdown;
    sf::Clock countdownTimer;
    int countdown;
    bool isWaveStarted;
    sf::Text countdownText;
    bool isGamePause;
    sf::Clock pauseDebounce;
    GameState::Status status;
    sf::Clock keyPressedClock;

    // sounds
    sf::SoundBuffer buildBuffer;
    sf::SoundBuffer upgradeBuffer;
    sf::SoundBuffer sellBuffer;
    sf::SoundBuffer clickBuffer;
    sf::SoundBuffer endBuffer;
    sf::SoundBuffer selectBuffer;
    sf::SoundBuffer towerBuffer;
    sf::SoundBuffer healthBuffer;
    sf::SoundBuffer arrowBuffer;
    sf::SoundBuffer magicBuffer;
    sf::SoundBuffer rockBuffer;
    sf::SoundBuffer waveBuffer;

    sf::Sound build;
    sf::Sound upgrade;
    sf::Sound sell;
    sf::Sound click;
    sf::Sound end;
    sf::Sound select;
    sf::Sound tower;
    sf::Sound health;
    sf::Sound arrow;
    sf::Sound magic;
    sf::Sound rock;
    sf::Sound wave;

    // delete later 
    bool mon_walk;

    // Functions
    void initKeybinds();
    void initTextures();
    void initCreator();
    void initPlayer();
    void initFont();
    void initButtons();
    void initPausedButtons();
    void initPausedMenu();
    void initEndButtons();
    void initEndMenu();
    void initScore();
    void initLevel();
    void initCountdown();
    void initTowerAreas();
    void initTowerCreatorPointers();
    void initSounds();
    void spawnMonsters();
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
    void nextLevel();
    void toggleStatePaused();
    void checkEndGame();
    void endGame();

    void highlightSelectedTowerCreator();

    void updateFreeAreas();
    void updateLevel();
    void updateEndLevel();
    void updateCountdown();
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
    void updatePausedMenu();
    void updateEndMenu();
    void updateAndSaveScore();
    void update(const float& dt);

    void destoryBullets();
    void destoryMonsters();

    void renderTowerCreatorPointers(sf::RenderTarget* target);
    void renderPausedMenu(sf::RenderTarget* target);
    void renderEndMenu(sf::RenderTarget* target);
    void renderTowerAreas(sf::RenderTarget* target);
    void renderLevel(sf::RenderTarget* target);
    void renderCountdown(sf::RenderTarget* target);
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
