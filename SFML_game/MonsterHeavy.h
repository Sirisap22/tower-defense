#pragma once
#include "Monster.h"
class MonsterHeavy :
    public Monster
{
private:
    void initComponents();
public:
    MonsterHeavy(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture& texture_sheet);
    virtual ~MonsterHeavy();
};

