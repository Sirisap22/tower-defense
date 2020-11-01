#pragma once
#include "Monster.h"
class MonsterNormal :
    public Monster
{
private:
    void initComponents();

public:
    MonsterNormal(float x, float y, Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture& texture_sheet);
    virtual ~MonsterNormal();
};

