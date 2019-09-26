#pragma once
#include "Map.h"
class House : public Map
{
public:
	House(CHAR_INFO *sprite, int x, int y, int width = SIZEW, int height = SIZEH);
	~House();
	bool House::IsHouse();
};

