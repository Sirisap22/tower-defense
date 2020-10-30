#pragma once
#include "Monster.h"
class MonsterFly :
    public Monster
{
private:
   virtual void initComponents();

public:
    MonsterFly(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture& texture_sheet);
    virtual ~MonsterFly();
};

