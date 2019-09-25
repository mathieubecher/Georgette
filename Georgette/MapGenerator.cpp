#include "pch.h"
#include "MapGenerator.h"
#include "Game.h"
#include <list>
#include <math.h>
#include <cstdlib>
#include <time.h>

MapGenerator::MapGenerator()
{
}


MapGenerator::~MapGenerator()
{
}

CHAR_INFO *MapGenerator::GenerateDirtBlock(Vector2 &size) {
	size_t n = 4 * 8;
	size = Vector2(8,4);
	CHAR_INFO *res = new CHAR_INFO[n];
	size_t randValue;
	for (size_t i = 0; i < n; ++i) {
		res[i].Char.UnicodeChar = ' ';
		res[i].Attributes = 0x00d0;
		if (std::rand() % n != 0) {
			randValue = std::rand() % 100;
			res[i].Attributes = 0x000f;
			if (randValue > 15) {
				res[i].Char.UnicodeChar = ' ';
			}
			else if (randValue > 11) {
				res[i].Char.UnicodeChar = '.';
			}
			else if (randValue > 8) {
				res[i].Char.UnicodeChar = 'o';
			}
			else if (randValue > 7) {
				res[i].Char.UnicodeChar = ',';
			}
			else if (randValue > 5) {
				res[i].Char.UnicodeChar = ';';
			}
			else if (randValue > 2) {
				res[i].Char.UnicodeChar = ':';
			}
			else if (randValue > 1) {
				res[i].Char.UnicodeChar = 'O';
			}
			else {
				res[i].Char.UnicodeChar = 'i';
			}
		}
	}
	return res;
}

void MapGenerator::PutSprite(CHAR_INFO *fullSprite, size_t x, size_t y) {
	CHAR_INFO *res;
	Vector2 size;
	res = GenerateDirtBlock(size);
	for (size_t i = 0; i < size.x; ++i) {
		for (size_t j = 0; j < size.y; ++j) {
			if ((i+x < SIZEW) && (j+y < SIZEH)) {
				fullSprite[(i + x) + SIZEW*(j + y)].Attributes = res[i + 8*j].Attributes;
				fullSprite[(i + x)+ SIZEW*(j + y)].Char = res[i + 8*j].Char;
			}
		}
	}
	delete [] res;
}

int MapGenerator::GetRandomFloorLevel() {
	int res = SIZEH - rand() % (SIZEH * 2 / 3);
	return res - (res % 4);
}

GenFormat MapGenerator::GenerateFormat(Map *left, Map *right, Map *top, Map *bottom) {
	GenFormat res;
	if (right) {
		res.right = right->format.left;
	}
	else if (rand()%10 != 0) {
		res.right = MapGenerator::GetRandomFloorLevel();
	}
	else {
		res.right = -1;
	}
	if (left) {
		res.left = left->format.right;
	}
	else if (rand() % 10 != 0) {
		res.left = MapGenerator::GetRandomFloorLevel();
	}
	else {
		res.left = -1;
	}
	if (top) {
		res.top = top->format.bottom;
	}
	else {
		res.top = rand() % 2 == 0;
	}
	if (bottom) {
		res.bottom = bottom->format.top;
	}
	else {
		res.bottom = rand() % 2 == 0;
	}
	return res;
}

Map *MapGenerator::GenerateFirstChunk() {
	srand(time(NULL));
	/*
	CHAR_INFO *sprite = new CHAR_INFO[SIZEW*SIZEH];
	for (size_t j = 0; j < SIZEW*SIZEH; ++j) {
		sprite[j].Attributes = 0x00d0;
		sprite[j].Char.UnicodeChar = ' ';
	}
	for (size_t i = 0; i < 10; ++i) {
		PutSprite(sprite,i*8,36);
	}
	Map *first = new Map(sprite, 0, 0);
	first->format = MapGenerator::GenerateFormat(nullptr,nullptr,nullptr,nullptr);
	return first;
	*/
	return GenerateChunk(Vector2(0,0));
}

Map *MapGenerator::GenerateChunk(Vector2 pos) {
	CHAR_INFO *sprite = new CHAR_INFO[SIZEW*SIZEH];
	for (size_t j = 0; j < SIZEW*SIZEH; ++j) {
		sprite[j].Attributes = 0x00d0;
		sprite[j].Char.UnicodeChar = ' ';
	}
	GenFormat format = MapGenerator::GenerateFormat(FindChunk(Vector2(pos.x-SIZEW,pos.y)), FindChunk(Vector2(pos.x + SIZEW, pos.y)), FindChunk(Vector2(pos.x, pos.y-SIZEH)), FindChunk(Vector2(pos.x, pos.y + SIZEH)));
	int floorLevel = format.left == -1 ? MapGenerator::GetRandomFloorLevel() : format.left;
	int targetLevel = format.right == -1 ? MapGenerator::GetRandomFloorLevel() : format.right;
	int sign = 0;
	if (targetLevel != floorLevel) {
		sign = (targetLevel - floorLevel) / abs(targetLevel - floorLevel);
	}
	for (size_t i = 0; i < 10; ++i) {
		if (floorLevel != targetLevel) {
			int randValue = rand() % 3;
			if (randValue == 0) {
				floorLevel += sign * 4;
			}
		}
		for (size_t j = SIZEH - floorLevel; j < SIZEH; j+=4) {
			PutSprite(sprite, i * 8, j);
		}
	}
	Map *res = new Map(sprite, 0, 0);
	res->format = format;
	return res;
}


Map *MapGenerator::FindChunk(Vector2 pos) {
	std::list<Map*> chunks = Game::GetChunks();
	for (auto i : chunks) {
		if (i->GetPos() == pos) {
			return i;
		}
	}
	return nullptr;
}