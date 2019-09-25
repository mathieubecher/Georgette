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
		if (std::rand() % (n*40) != 0) {
			randValue = std::rand() % 300;
			res[i].Attributes = 0x000f;
			if (randValue > 10) {
				res[i].Char.UnicodeChar = ' ';
			}
			else if (randValue > 5) {
				res[i].Char.UnicodeChar = '.';
			}
			else if (randValue > 0) {
				res[i].Char.UnicodeChar = 'o';
			}
			else {
				res[i].Char.UnicodeChar = 'O';
			}
		}
	}
	return res;
}

size_t MapGenerator::CountEmptyAdjacent(CHAR_INFO *fullSprite, size_t i, size_t j) {
	size_t res = 0;
	if (i > 0 && fullSprite[i-1 + (j*SIZEW)].Attributes == 0x00d0) {
		++res;
	}
	if (j > 0 && fullSprite[i + ((j-1)*SIZEW)].Attributes == 0x00d0) {
		++res;
	}
	if ( i +1 < SIZEW && fullSprite[i+1+(j*SIZEW)].Attributes == 0x00d0) {
		++res;
	}
	if (j + 1 < SIZEW && fullSprite[i + ((j+1)*SIZEW)].Attributes == 0x00d0) {
		++res;
	}
	return res;
}

void MapGenerator::Erosion(CHAR_INFO *fullSprite) {
	CHAR_INFO *oldSprite = new CHAR_INFO[SIZEW*SIZEH];
	for (size_t i = 0; i < SIZEW*SIZEH; ++i) {
		oldSprite[i] = fullSprite[i];
	}
	for (size_t i = 0; i < SIZEW; ++i) {
		for (size_t j = 0; j < SIZEH; ++j) {
			if (CountEmptyAdjacent(oldSprite, i, j) > 1 && rand()%2 > 0) {
				fullSprite[i + j*SIZEW].Attributes = 0x00d0;
				fullSprite[i + j*SIZEW].Char.UnicodeChar = ' ';
			}
		}
	}
	delete[] oldSprite;
}

void MapGenerator::GrassGenerator(CHAR_INFO *fullSprite) {
	for (size_t i = 0; i < SIZEW; ++i) {
		for (size_t j = 0; j < SIZEH; ++j) {
			if (j + 1 < SIZEH && fullSprite[i + j*SIZEW].Attributes == 0x00d0 && fullSprite[i + (j+1)*SIZEW].Attributes == 0x000f) {
				size_t randValue = rand() % 100;
				if (randValue > 60) {
					fullSprite[i + j*SIZEW].Char.UnicodeChar = '.';
				}
				else if (randValue > 30) {
					fullSprite[i + j*SIZEW].Char.UnicodeChar = ',';
				}
				else if (randValue > 5){
					fullSprite[i + j*SIZEW].Char.UnicodeChar = '_';
				}
				else if (randValue > 2) {
					fullSprite[i + j*SIZEW].Char.UnicodeChar = '\\';
				}
				else {
					fullSprite[i + j*SIZEW].Char.UnicodeChar = '/';
				}
			}
		}
	}
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
	Map * res = GenerateChunk(Vector2(0,0));
	GenerateChunk(Vector2(SIZEW, 0));
	GenerateChunk(Vector2(-SIZEW, 0));
	GenerateChunk(Vector2(0, SIZEH));
	GenerateChunk(Vector2(0, -SIZEH));
	return res;
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
	if (format.left == -1) {
		for (size_t j = 0; j < SIZEH; j += 4) {
			PutSprite(sprite, 0, j);
		}
	}
	if (format.right == -1) {
		for (size_t j = 0; j < SIZEH; j += 4) {
			PutSprite(sprite, SIZEW-8, j);
		}
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
	for (size_t i = 0; i < 5; ++i) {
		Erosion(sprite);
	}
	GrassGenerator(sprite);
	Map *res = new Map(sprite, pos.x, pos.y);
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