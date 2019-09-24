#pragma once
#include "Physic2D.h"
class Collidable : public Physic2D
{
public:
	bool Collider(Vector2f pos, Vector2 size);
};

