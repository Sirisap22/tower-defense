#pragma once
#include "Tower.h"
class TowerHeavy :
    public Tower
{
private:
public:
    TowerHeavy(float x, float y, Entity::EntityAttributes attribute, int damage, int attack_speed, std::map<std::string, sf::Texture> textures);
    virtual ~TowerHeavy();

};


