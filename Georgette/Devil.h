#pragma once
#include "Rigidbody.h"
#define SPEED 0.5f
#define JUMP -0.3f

class Devil : public Rigidbody
{
private:
public :
	Devil(int x, int y);
	void Update();
	void Move(bool direction = true);
	bool Jump();
};

