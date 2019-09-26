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
#include "Devil.h"

#define MAXFRAME 60
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
	Vector2 posChange;

	
	std::list<Physic2D*> objects;
	std::list<Map*> chunks;
	std::list<Collidable*> collidables;
	
	void Update();
	void Draw();

	Game();
	~Game();

	int i;
	float wait;
	float screenshake;
public:
	Devil georgette;
	NYTimer time;
	static Game * Get();
	static std::list<Map*> GetChunks();
	static std::list<Collidable*> GetCollidables();
	static std::list<Physic2D*> GetObjects();
	
	CHAR_INFO * Buffer();
	Vector2 Pos();
	Vector2 RealPos();
	void SetPos(int x, int y);
	void AddObject(Physic2D * p);
	void AddChunk(Map * m);
	void AddCollidable(Collidable * c);
	void RemoveObject(Physic2D * p);
	void RemoveChunk(Map * m);
	void RemoveCollidable(Collidable * c);
	void Run();
	float DistanceToCam(Vector2f pos);
	void Wait(float wait);
	void ScreenShake(float time, int force);
};
