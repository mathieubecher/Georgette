#pragma once
#include "Physic2D.h"
#define SIZEW 80
#define SIZEH 40
#include <list>
class Map: public Physic2D
{
public:
	static Map *originalChunk;

	Map(CHAR_INFO *sprite, int x, int y, int width = SIZEW, int height = SIZEH);

	Box Collider(Vector2f pos, Vector2 size);
	std::list<CHAR_INFO*> CollideCase(Vector2f pos, Vector2 size);

	Map(std::string file, int x = 0, int y = 0, int width = 1, int height = 1);
};