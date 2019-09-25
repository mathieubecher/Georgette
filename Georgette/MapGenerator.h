#pragma once
#include "Map.h"
class MapGenerator
{
public:
	static Vector2 const SIZE;
	MapGenerator();
	~MapGenerator();
	static Map *GenerateChunk(Vector2 pos);
	static Map *FindChunk(Vector2 pos);
	static Map *GenerateFirstChunk();
	static void PutSprite(CHAR_INFO *fullSprite, size_t x, size_t y);
	static CHAR_INFO *GenerateDirtBlock(Vector2 &size);
	static GenFormat GenerateFormat(Map *left, Map *right, Map *top, Map *bottom);
	static int GetRandomFloorLevel();
};