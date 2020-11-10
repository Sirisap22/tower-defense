#pragma once

#include "Monster.h"
#include "Tower.h"
#include <cmath>

class Bullet :
    public Entity
{
private:
    int level;
    Tower* tower;
    Monster* target;
    Entity::EntityAttributes attribute;
    std::vector<sf::Texture> textureBulletLevelN;
    sf::Vector2f origin;

    std::string selectTexturesByAttribute();
    void initComponents();
    void initTextures(std::map<std::string, sf::Texture> textures);
public:
    Bullet(float x, float y, Entity::EntityAttributes attribute, int level, Tower* tower, Monster* target, std::map<std::string, sf::Texture> textures);
    virtual ~Bullet();

    Tower* getTower() const;
    Monster* getTarget() const;

    virtual void setTextureByLevel();

    virtual sf::Vector2f relativeTargetPosition();
    virtual void rotateRelativeTextureAngle();

    virtual void render(sf::RenderTarget* target);
    virtual void shoot(const float& dt);
};

