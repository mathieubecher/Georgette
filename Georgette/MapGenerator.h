#pragma once
#include "Map.h"
class MapGenerator
{
public:
	static Vector2 const SIZE;
	MapGenerator();
	~MapGenerator();
	Map *GenerateChunk(Vector2 pos);
	Map *FindChunk(Vector2 pos);
	Map *GenerateFirstChunk();
};