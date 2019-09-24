#pragma once
#include "Collidable.h"
#include "Physic2D.h"
class Rigidbody : public Collidable
{
private :
	float velocity;
public:
	void Update();
	Rigidbody(std::string file, int x = 0, int y = 0, int width = 1, int height = 1);
};

