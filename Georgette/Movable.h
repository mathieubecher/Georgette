#pragma once
#include "Collidable.h"
#include "Physic2D.h"
class Movable : public Collidable
{
private :
	float velocity;
public:
	void Update();
};

