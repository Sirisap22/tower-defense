#pragma once

#include "Monster.h"
#include "Entity.h"
#include "cmath"

class Bullet :
    public Entity
{
private:
    int level;
    Monster* target;
    Entity::EntityAttributes attribute;
    std::vector<sf::Texture> textureBulletLevelN;
    sf::Vector2f origin;

    std::string selectTexturesByAttribute();
    void initComponents();
    void initTextures(std::map<std::string, sf::Texture> textures);
public:
    bool isCollide;
    Bullet(float x, float y, Entity::EntityAttributes attribute, int level, Monster* target, std::map<std::string, sf::Texture> textures);
    virtual ~Bullet();

    virtual void setTextureByLevel();

    virtual sf::Sprite* getSprite();

    virtual Monster* getTarget() const;
    virtual sf::Vector2f relativeTargetPosition();
    
    virtual void update(const float& dt, float angle);
    virtual void render(sf::RenderTarget* target);
   };

