#pragma once
#include "Entity.h"
class MonsterHeavy :
    public Entity
{
private:
    int health, damage;
    float walkSpeed;

    void initVariables(int health, std::string skill, float walk_speed, int damage);

public:
    std::string skill;

    MonsterHeavy(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture& texture_sheet);
    virtual ~MonsterHeavy();

    // functions
    virtual void update(const float& dt);
};

