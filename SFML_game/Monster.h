#pragma once
#include "Entity.h"
class Monster :
    public Entity
{
private:
    void initVariables(int health, std::string skill, float walk_speed, int damage);
    virtual void initComponents(sf::Texture& texture_sheet) = 0;

protected:
    int health, damage;
    float walkSpeed;

public:
    std::string skill;

    Monster(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture& texture_sheet);
    virtual ~Monster();

    // functions
    virtual void update(const float& dt);
};

