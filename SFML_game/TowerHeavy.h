#pragma once
#include "Tower.h"
class TowerHeavy :
    public Tower
{
private:
public:
    TowerHeavy(float x, float y, int damage, int attack_speed, sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3);
    virtual ~TowerHeavy();
};


