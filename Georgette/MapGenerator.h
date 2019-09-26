#pragma once
#include "Map.h"
class MapGenerator
{
public:
	static CHAR_INFO *castle;
	static CHAR_INFO *building;
	static Vector2 sizes[5];
	MapGenerator();
	~MapGenerator();
	static Map *GenerateChunk(Vector2 pos);
	static Map *FindChunk(Vector2 pos);
	static Map *GenerateFirstChunk();
	static void PutSprite(CHAR_INFO *fullSprite, size_t x, size_t y, bool stalactite = false);
	static CHAR_INFO *GenerateDirtBlock(Vector2 &size);
	static CHAR_INFO *GenerateStalactite(Vector2 &size);
	static GenFormat GenerateFormat(Map *left, Map *right, Map *top, Map *bottom);
	static int GetRandomFloorLevel();
	static void Erosion(CHAR_INFO *fullSprite);
	static size_t CountEmptyAdjacent(CHAR_INFO *fullSprite, size_t i, size_t j);
	static void GrassGenerator(CHAR_INFO *fullSprite);
	static void Update();
	static Vector2 GetStartingMapPos(Vector2 pos);
	static void PutHouse(CHAR_INFO *house, Vector2 size, Vector2 pos, CHAR_INFO *fullSprite, size_t x, size_t y);
	static void InitHouses();
};