#pragma once
#include "Entity.h"
class TowerNormal :
    public Entity
{
private:
    int level;
    int damage;
    int attackSpeed;
    std::vector<sf::Texture&> textureTowerLevelN;

    void initVariables(int damage, int attack_speed);
    void initTextures(sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3);

public:
    TowerNormal(float x, float y, int damage, int attack_speed, sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3);
    virtual ~TowerNormal();

    virtual void update(const float& dt);

    virtual void upgrade(int level);
    virtual void attack();
};

