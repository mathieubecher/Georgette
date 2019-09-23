#pragma once
#include "Windows.h"
#include <stdio.h>
#include <iostream>
#include "NYTimer.h"

#define MAXFRAME 30.0f
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

class Game
{
private:
	HANDLE hOutput;
	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	NYTimer time;
	int i;
	

	void Instantiate();
	void Update();
	void Draw();


public:
	Game();
	~Game();
	
};
