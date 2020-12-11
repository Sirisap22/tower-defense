#pragma once
#include "Plane.h"
class GoalsPlane :
    public Plane
{
private:
	void initHeader(unsigned header_character_size);
	void initContent(unsigned content_character_size);
public:
	GoalsPlane(float x, float y, float width, float height,
		sf::Font* font, unsigned header_character_size, unsigned content_character_size);
	virtual ~GoalsPlane();
};

