#pragma once
#include <windows.h>
#include <stdio.h>

#include "Rigidbody.h"

#define SPEED 0.5f
#define JUMP -0.3f
#define COYOTE 100

class Devil : public Rigidbody
{
private:
	float coyote;
	bool jumping;
	Sprite iddle_left;
	Sprite iddle_right;
	
	float assshotScore;
	bool asshotinputpress;
	
	void UpdateAssShot();

public :
	bool assshot;
	Devil(int x, int y);
	void Update();
	void Move(bool direction = true);
	bool Jump();
	void AssShot();
	void Init(int x, int y);
};

