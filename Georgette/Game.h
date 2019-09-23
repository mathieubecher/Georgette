#pragma once
#include "Windows.h"
#include <stdio.h>
#include <iostream>
#include "NYTimer.h"
#include "Sprite.h"

#define MAXFRAME 120.0f
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

class Game
{
private:
	HANDLE hOutput;
	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	NYTimer time;
	
	Sprite objet;

	static Game * game;

	void Update();
	void Draw();

	Game();
	~Game();

	int i;

public:
	static Game * Get();
	CHAR_INFO * Buffer();
	void Run();
};
