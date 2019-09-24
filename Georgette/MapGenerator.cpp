#include "pch.h"
#include "MapGenerator.h"
#include "Game.h"
#include <list>
#include <math.h>

MapGenerator::MapGenerator()
{
}


MapGenerator::~MapGenerator()
{
}

Map *MapGenerator::GenerateFirstChunk() {
	CHAR_INFO sprite[SIZEW*SIZEH];







	Map first = Map(sprite, 0, 0);
	return nullptr;
}

Map *MapGenerator::GenerateChunk(Vector2 pos) {

	return nullptr;
}


Map *MapGenerator::FindChunk(Vector2 pos) {
	std::list<Map*> *chunks = Game::GetChunks();
	for (Map* i : *chunks) {
		if (i->GetPos() == pos) {
			return i;
		}
	}
	return nullptr;
}