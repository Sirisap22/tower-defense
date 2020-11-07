#pragma once
#include "Entity.h"
class Bullet :
    public Entity
{
private:
    int damage;
    float maxVelocity;
    float acceleration;

    void initVariables();
    void initComponents();

public:
    Bullet(float x, float y, int damage, float maxVelocity, float acceleration,
            sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3);
    virtual ~Bullet();

    virtual void fire(float movementX, float movementY, float delay);
    virtual void updateHitboxPosition(sf::Vector2f currentPosition);
    virtual void update(const float& dt);
};

