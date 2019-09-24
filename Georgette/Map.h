#pragma once
#include "Physic2D.h"
class Map: public Physic2D
{
public:
	static Map *originalChunk;


	Map(std::string file, int x = 0, int y = 0, int width = 1, int height = 1);
};

