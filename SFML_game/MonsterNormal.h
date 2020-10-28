#pragma once
#include "Entity.h"

class MonsterNormal :
    public Entity
{
private:
    int health, damage;
    float walkSpeed;
    

    void initVariables(int health, std::string skill, float walk_speed, int damage);

public:
    std::string skill;

    MonsterNormal(float x, float y, int health, std::string skill,float walk_speed,int damage, sf::Texture& texture_sheet);
    virtual ~MonsterNormal();

    // functions
    virtual void update(const float& dt);
};

