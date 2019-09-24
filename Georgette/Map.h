#pragma once
#include "Physic2D.h"
#define SIZEW 80
#define SIZEH 40

class Map: public Physic2D
{
public:
	static Map *originalChunk;

	Map(CHAR_INFO *sprite, int x, int y, int width = SIZEW, int height = SIZEH) {
	}

	bool Collider(Vector2f pos, Vector2 size);
	Map(std::string file, int x = 0, int y = 0, int width = 1, int height = 1);
};