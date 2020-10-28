#pragma once
#include "Monster.h"
class MonsterNormal :
    public Monster
{
private:
    virtual void initComponents(sf::Texture& texture_sheet);

public:
    MonsterNormal(float x, float y, int health, std::string skill, float walk_speed, int damage, sf::Texture& texture_sheet);
    virtual ~MonsterNormal();
};

