#pragma once
#include "Windows.h"
#include <stdio.h>
#include <iostream>
#include "NYTimer.h"
#include "Physics2D.h"

#define MAXFRAME 30.0f
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

class Game
{
private:
	HANDLE hOutput;
	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	NYTimer time;
	
	Physics2D objet;

	static Game * game;

	void Update();
	void Draw();

	Game();
	~Game();

	int i;

public:
	static Game * Get();
	CHAR_INFO * Buffer();
};
