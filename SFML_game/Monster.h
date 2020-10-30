#pragma once
#include "Entity.h"
class Monster :
    public Entity
{
protected:
    int health, damage;
    float walkSpeed;
    sf::Texture textureSheet;

    void initVariables(int health, std::string skill, float walk_speed, int damage, sf::Texture texture_sheet);
   

public:
    std::string skill;

    Monster(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture texture_sheet);
    virtual ~Monster();

    // functions
    virtual void update(const float& dt);
    virtual void initComponents() = 0;
};

