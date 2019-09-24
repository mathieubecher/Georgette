#pragma once
#include "Physic2D.h"
class Collidable : public Physic2D
{
public:
	bool Collider(Vector2f pos, Vector2 size);
	Collidable(std::string file, int x = 0, int y = 0, int width = 1, int height = 1);
};

