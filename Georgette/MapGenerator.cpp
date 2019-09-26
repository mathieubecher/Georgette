#include "pch.h"
#include "MapGenerator.h"
#include "Game.h"
#include <list>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include "House.h"

CHAR_INFO *MapGenerator::castle;
CHAR_INFO *MapGenerator::building;
Vector2 MapGenerator::sizes[5];

MapGenerator::MapGenerator()
{
}


MapGenerator::~MapGenerator()
{
}


CHAR_INFO *MapGenerator::GenerateStalactite(Vector2 &size) {
	size_t n = 4 * 8;
	size = Vector2(8, 4);
	CHAR_INFO *res = new CHAR_INFO[n];
	for (size_t i = 0; i < n; ++i) {
		res[i].Char.UnicodeChar = ' ';
		res[i].Attributes = 0x00d0;
	}
	size_t randValue;
	bool descend = true;
	size_t level = 0;
	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < level+1 && j < 4; ++j) {
			if (rand() % 3 == 0) {
				if (descend) {
					++level;
					if (level > 3) {
						descend = false;
					}
				}
				else {
					--level;
				}
			}
			res[i+8*j].Attributes = 0x000f;
			randValue = std::rand() % 300;
			if (randValue > 10) {
				res[i + 8 * j].Char.UnicodeChar = ' ';
			}
			else if (randValue > 5) {
				res[i + 8 * j].Char.UnicodeChar = '.';
			}
			else if (randValue > 0) {
				res[i + 8 * j].Char.UnicodeChar = 'o';
			}
			else {
				res[i + 8 * j].Char.UnicodeChar = 'O';
			}
		}
	}
	return res;
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
	if (j + 1 < SIZEH && fullSprite[i + ((j+1)*SIZEW)].Attributes == 0x00d0) {
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
			else if((i > 0 && oldSprite[i-1+j*SIZEW].Attributes== 0x00d0) || (i+1 < SIZEW && oldSprite[i+1+j*SIZEW].Attributes == 0x00d0) && rand()%10 ==0) {
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

void MapGenerator::PutHouse(CHAR_INFO *house, Vector2 size, Vector2 pos, CHAR_INFO *fullSprite, size_t x, size_t y) {
	CHAR_INFO *res = new CHAR_INFO[size.x * size.y];
	for (size_t i = 0; i < size.x * size.y; ++i) {
		res[i].Attributes = house[i].Attributes;
		res[i].Char.UnicodeChar = house[i].Char.UnicodeChar;
	}
	for (size_t i = 0; i < size.x; ++i) {
		for (size_t j = 0; j < size.y; ++j) {
			if ((i + x < SIZEW) && (j + y < SIZEH)) {
				fullSprite[(i + x) + SIZEW*(j + y)].Attributes = 0x00d0;
				fullSprite[(i + x) + SIZEW*(j + y)].Char.UnicodeChar = ' ';
			}
		}
	}
	House *h = new House(res, pos.x, pos.y, size.x, size.y);
}

void MapGenerator::PutSprite(CHAR_INFO *fullSprite, size_t x, size_t y, bool stalactite) {
	CHAR_INFO *res;
	Vector2 size;
	if (!stalactite) {
		res = GenerateDirtBlock(size);
	}
	else {
		res = GenerateStalactite(size);
	}
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
	int res = 4 + (rand() % (SIZEH*2/3));
	return res - (res % 4);
}

void MapGenerator::Update() {
	int xpos = Game::Get()->Pos().x;
	int ypos = Game::Get()->Pos().y;
	size_t const n = 12;
	Vector2 pos[n];
	pos[0] = GetStartingMapPos(Vector2(xpos,ypos));
	pos[1] = Vector2(pos[0].x + SIZEW, pos[0].y);
	pos[2] = Vector2(pos[0].x - SIZEW, pos[0].y);
	pos[3] = Vector2(pos[0].x, pos[0].y + SIZEH);
	pos[4] = Vector2(pos[0].x, pos[0].y - SIZEH);
	pos[5] = Vector2(pos[0].x + SIZEW, pos[0].y + SIZEH);
	pos[6] = Vector2(pos[0].x - SIZEW, pos[0].y + SIZEH);
	pos[7] = Vector2(pos[0].x + SIZEW, pos[0].y - SIZEH);
	pos[8] = Vector2(pos[0].x - SIZEW, pos[0].y - SIZEH);
	pos[9] = Vector2(pos[0].x + 2*SIZEW, pos[0].y + SIZEH);
	pos[10] = Vector2(pos[0].x + 2*SIZEW, pos[0].y - SIZEH);
	pos[11] = Vector2(pos[0].x + 2*SIZEW, pos[0].y);


	for (size_t i = 0; i < n; ++i) {
		if (!FindChunk(pos[i])) {
			GenerateChunk(pos[i]);
		}
	}
}


Vector2 MapGenerator::GetStartingMapPos(Vector2 pos) {
	int x = pos.x;
	int y = pos.y;
	x = x - (x % SIZEW);
	y = y - (y % SIZEH);
	return Vector2(x,y);
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
		res.top = rand() % 5 == 0;
	}
	if (bottom) {
		res.bottom = bottom->format.top;
	}
	else {
		res.bottom = rand() % 5 == 0;
	}
	return res;
}

Map *MapGenerator::GenerateFirstChunk() {
	srand(time(NULL));
	InitHouses();
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
		if (!format.bottom || i < 4 || i > 6) {
			for (size_t j = SIZEH - floorLevel; j < SIZEH; j += 4) {
					PutSprite(sprite, i * 8, j);
			}
		}
	}
	for (size_t i = 0; i < 7; ++i) {
		Erosion(sprite);
	}
	for (size_t i = 0; i < 10; ++i) {
		if (rand() % 3 == 0 && (i!=0 || format.left!=-1) && (i != 9 || format.right!=-1) && ((i > 7)||(i<3) || !format.top)) {
			PutSprite(sprite, i*8, 0, true);
		}
	}
	GrassGenerator(sprite);
	if (!format.bottom) {
		if (rand()%2 == 0) {
			size_t randValue = 5 + rand() % (SIZEW - 5 - sizes[0].x);
			for (size_t j = 0; j + sizes[0].y + 1 < SIZEH; ++j) {
				if (sprite[randValue + SIZEW*j].Attributes == 0x00d0 && sprite[randValue + SIZEW*(j + 1)].Attributes == 0x000f) {
					PutHouse(building, sizes[0], Vector2(pos.x + randValue, pos.y + j + 1 - sizes[0].y), sprite, randValue, j + 1 - sizes[0].y);
				}
			}
		}
		else if(rand()%5 == 0) {
			size_t randValue = 5 + rand() % 8;
			for (size_t k = 0; k < 7; ++k) {
				for (size_t j = 0; j + sizes[0].y + 1 < SIZEH; ++j) {
					if (sprite[randValue + SIZEW*j].Attributes == 0x00d0 && sprite[randValue + SIZEW*(j + 1)].Attributes == 0x000f) {
						PutHouse(building, sizes[0], Vector2(pos.x + randValue, pos.y + j + 1 - sizes[0].y), sprite, randValue, j + 1 - sizes[0].y);
					}
				}
				randValue += 4 + (rand() % 5);
			}
		}
	}
	Map *res = new Map(sprite, pos.x, pos.y);
	res->format = format;
	return res;
}


Map *MapGenerator::FindChunk(Vector2 pos) {
	std::list<Map*> chunks = Game::GetChunks();
	for (auto i : chunks) {
		if (i->IsHouse()) {
			continue;
		}
		if (i->GetPos() == pos) {
			return i;
		}
		// Là aussi c'est dangereux !!
		else if ((i->GetPos().x > pos.x - SIZEW &&  i->GetPos().x < pos.x + SIZEW) && (i->GetPos().y > pos.y - SIZEH &&  i->GetPos().y < pos.y + SIZEH)){
			return i;
		}
	}
	return nullptr;
}

void MapGenerator::InitHouses() {
	//castle = SpriteGenerator::CreateSprite("houses/castle.spr", &sizes[0], nullptr);
	/*castle = new CHAR_INFO[11*5];
	for () {

	}
	sizes[0] = Vector2(11,5);*/

	sizes[0] = Vector2(3,4);
	building = new CHAR_INFO[3 * 4];
	building[0].Attributes = 0x00d0;
	building[0].Char.UnicodeChar = '_';
	building[1].Attributes = 0x00d0;
	building[1].Char.UnicodeChar = '_';
	building[2].Attributes = 0x00d0;
	building[2].Char.UnicodeChar = '#';
	for (size_t i = 3; i < 3 * 4; ++i) {
		building[i].Attributes = 0x000f;
		building[i].Char.UnicodeChar = '|';
	}
}