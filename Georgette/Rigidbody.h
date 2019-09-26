#pragma once
#include "Collidable.h"
#include "Physic2D.h"

#define GRAVITY 0.01f

class Rigidbody : public Collidable
{
protected :
	float velocity;
	bool onfloor;
public:
	void Update();
	void SetVelocity(float v);
	Rigidbody(std::string file, int x = 0, int y = 0, int width = 1, int height = 1,bool includeCircle = true);
};

