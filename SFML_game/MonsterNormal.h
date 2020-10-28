#pragma once
#include "Entity.h"

class MonsterNormal :
    public Entity
{
private:
    int health;
    void initVariables(int health);

public:
    MonsterNormal(float x, float y, int health, sf::Texture& texture_sheet);
    virtual ~MonsterNormal();

    // functions
    virtual void update(const float& dt);
};

