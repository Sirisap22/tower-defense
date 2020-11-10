#pragma once
#include <cmath>
#include "Entity.h"
class Monster :
    public Entity
{
protected:
    void initVariables(Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture texture_sheet);

public:
    int health, damage;
    float walkSpeed;
    Entity::EntityAttributes attribute;
    sf::Vector2f originPoint;
    sf::Texture textureSheet;

    Monster(float x, float y, Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture texture_sheet);
    virtual ~Monster();

    // functions
    virtual void update(const float& dt);
    virtual void decreaseHealth(int damage);
    virtual void initComponents() = 0;
};

