#pragma once
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <list>

#include "NYTimer.h"
#include "Sprite.h"
#include"Vector.h"
#include"Physic2D.h"
#include "Collidable.h"
#include "Map.h"


#define MAXFRAME 60.0f
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

#define WIDTH 500
#define HEIGHT 500

class Game
{
private:
	HANDLE hOutput;
	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	
	Vector2 pos;

	
	std::list<Physic2D*> objects;
	std::list<Map*> chunks;
	std::list<Collidable*> collidables;

	void Update();
	void Draw();

	Game();
	~Game();

	int i;

public:
	NYTimer time;
	static Game * Get();
	static std::list<Map*> GetChunks();
	static std::list<Collidable*> GetCollidables();
	static std::list<Physic2D*> GetObjects();
	
	CHAR_INFO * Buffer();
	Vector2 Pos();
	void SetPos(int x, int y);
	void AddObject(Physic2D * p);
	void AddChunk(Map * m);
	void AddCollidable(Collidable * c);
	void Run();
};
