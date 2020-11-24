#pragma once
#include "Plane.h"
class InputFieldPlane :
    public Plane
{
private:
    virtual void initHeader(unsigned header_character_size);
    virtual void initContent(unsigned content_character_size);
public:
    InputFieldPlane(float x, float y, float width, float height,
        sf::Font* font, unsigned header_character_size, unsigned content_character_size);
    virtual ~InputFieldPlane();

    void render(sf::RenderTarget* target);
};

