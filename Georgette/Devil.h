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
	HANDLE hStdin;
	INPUT_RECORD irInBuf[124];
	DWORD cNumRead;
	DWORD numEvent;


	float coyote;
	bool jumping;

public :
	Devil(int x, int y);
	void Update();
	void Move(bool direction = true);
	bool Jump();
};

