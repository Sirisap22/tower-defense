#pragma once
#include "Tower.h"
class TowerNormal :
    public Tower
{
private:
public:
    TowerNormal(float x, float y, Entity::EntityAttributes attribute, int damage, int attack_speed, std::map<std::string, sf::Texture> textures);
    virtual ~TowerNormal();

};

