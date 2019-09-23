#pragma once
#include "Windows.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

class Game
{
private:
	HANDLE hOutput;
	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	int i;
	void Update();
	void Draw();


public:
	Game();
	~Game();
	
};
