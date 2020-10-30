#pragma once
#include "Tower.h"
class TowerNormal :
    public Tower
{
private:
public:
    TowerNormal(float x, float y, int damage, int attack_speed, sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3);
    virtual ~TowerNormal();
};

