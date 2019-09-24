#pragma once
#include "Rigidbody.h"
#define SPEED 0.5f

class Devil : public Rigidbody
{
private:
public :
	Devil(int x, int y);
	void Update();
	void Move(bool direction = true);
};

