#pragma once

#include <algorithm>

#include "Monster.h"

class Tower :
    public Entity
{
protected:
    void initVariables(Entity::EntityAttributes attribute, int damage, int attack_speed);
    void initTextures(std::map<std::string, sf::Texture> textures);
    
    std::string selectTexturesByAttribute();
public:
    int level;
    int damage;
    int attackSpeed;
    float radius;
    sf::CircleShape radiusShape;
    sf::Clock time;

    Entity::EntityAttributes attribute;
    sf::Vector2f originPoint;
    std::vector<sf::Texture> textureTowerLevelN;
    std::vector<Monster*> monstersInRadius;
    

    Tower(float x, float y, Entity::EntityAttributes attribute,int damage, int attack_speed, std::map<std::string, sf::Texture> textures);
    virtual ~Tower();

    virtual bool isAlreadyDetected(Monster* monster);
    virtual bool canAttack();
    virtual std::vector<Monster*>::iterator monsterIterator(Monster* monster);
    virtual void render(sf::RenderTarget* target);
    virtual void update(const float& dt);
    
    //virtual void upgrade(int level) = 0;
    //virtual void attack() = 0;
};

