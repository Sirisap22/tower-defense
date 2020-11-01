#pragma once
#include "Monster.h"
class MonsterHeavy :
    public Monster
{
private:
    void initComponents();
public:
    MonsterHeavy(float x, float y, Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture& texture_sheet);
    virtual ~MonsterHeavy();
};

