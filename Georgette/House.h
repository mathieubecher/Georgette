#pragma once
#include "Map.h"
#include "Particle.h"
class House : public Map
{
public:
	House(CHAR_INFO *sprite, int x, int y, int width = SIZEW, int height = SIZEH);
	~House();
	bool IsHouse();
	void Update();
	void AddPeople(int x, int y);
};

