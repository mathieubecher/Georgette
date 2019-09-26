#pragma once
#include "Rigidbody.h"
#include <stdio.h>
#include <list>
#define SPEED 0.1f

class People:public Rigidbody
{
public:
	bool direction;
	bool die;
	float countdown;
	void Update();
	People(int x, int y);
	~People();
	Box Collider(Vector2f pos, Vector2 size);
};

