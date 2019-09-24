#include "pch.h"
#include "MapGenerator.h"
#include "Game.h"
#include <list>
#include <math.h>
#include <cstdlib>

MapGenerator::MapGenerator()
{
}


MapGenerator::~MapGenerator()
{
}

void MapGenerator::PutSprite(CHAR_INFO *fullSprite, size_t x, size_t y, std::string fileName) {
	CHAR_INFO *res;
	Vector2 size;
	res = SpriteGenerator::CreateSprite(fileName, &size);
	for (size_t i = 0; i < size.x; ++i) {
		for (size_t j = 0; j < size.y; ++j) {
			if ((i+x < SIZEW) && (j+y < SIZEH)) {
				fullSprite[(i + x)*(j + y)] = res[i*j];
			}
		}
	}
	delete(res);
}

Map *MapGenerator::GenerateFirstChunk() {
	CHAR_INFO *sprite = new CHAR_INFO[SIZEW*SIZEH];
	for (size_t i = 0; i < 10; ++i) {
		std::string rand = std::to_string(std::rand()%6);
		PutSprite(sprite,i*8,36,"../resources/sprites/tile/floor"+rand+".spr");
		return nullptr;
	}
	//Map first = Map(sprite, 0, 0);
	//return &first;
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