#pragma once
#include "Tower.h"
class TowerFly :
    public Tower
{
private:
public:
    TowerFly(float x, float y, Entity::EntityAttributes attribute, int damage, int attack_speed, std::map<std::string, sf::Texture> textures);
    virtual ~TowerFly();
};

