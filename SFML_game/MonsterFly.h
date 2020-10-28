#pragma once
#include "Entity.h"
class MonsterFly :
   public Entity
{
private:
    int health, damage;
    float walkSpeed;

    void initVariables(int health, std::string skill, float walk_speed, int damage);

public:
    std::string skill;

    MonsterFly(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture& texture_sheet);
    virtual ~MonsterFly();

    // functions
    virtual void update(const float& dt);
};

