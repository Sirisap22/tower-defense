#pragma once

#include <algorithm>

#include "Entity.h"
#include "Monster.h"

class Tower :
    public Entity
{
protected:
    void initVariables(Entity::EntityAttributes attribute, int damage, int attack_speed);
    void initTextures(sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3);

public:
    int level;
    int damage;
    int attackSpeed;
    float radius;
    sf::CircleShape radiusShape;
    Entity::EntityAttributes attribute;
    sf::Vector2f originPoint;
    std::vector<sf::Texture> textureTowerLevelN;
    std::vector<Monster*> monstersInRadius;

    Tower(float x, float y, Entity::EntityAttributes attribute,int damage, int attack_speed, sf::Texture& level_1, sf::Texture& level_2, sf::Texture& level_3);
    virtual ~Tower();

    virtual bool isAlreadyDetected(Monster* monster);
    virtual std::vector<Monster*>::iterator monsterIterator(Monster* monster);
    virtual void attack();

    virtual void render(sf::RenderTarget* target);
    virtual void update(const float& dt);
    
    //virtual void upgrade(int level) = 0;
    //virtual void attack() = 0;
};

