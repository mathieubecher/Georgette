#pragma once
#include "Collidable.h"
class Particle : public Collidable
{
private:
	float value;
public:
	float timeDelete;
	Particle(int x, int y);
	void Update();
	void Draw();
	Box Collider(Vector2f pos, Vector2 size);
};

