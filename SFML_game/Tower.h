#pragma once
#include <queue>

#include "Entity.h"
#include "Monster.h"

class Tower :
    public Entity
{
private:
    int level;
    int damage;
    int attackSpeed;
    std::vector<sf::Texture> textureTowerLevelN;
    std::queue<Monster*> monstersInRadius;

    void initVariables(int damage, int attack_speed);
    void initTextures(sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3);

public:
    Tower(float x, float y,int damage, int attack_speed, sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3);
    virtual ~Tower();

    virtual void update(const float& dt);

    virtual void upgrade(int level) = 0;
    virtual void attack() = 0;
};

