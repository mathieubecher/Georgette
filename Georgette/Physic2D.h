#pragma once
#include "Sprite.h"
class Physic2D
{
protected:
	Sprite sprite;
	Vector2f pos;
	Vector2f size;
public:
	Physic2D();
	Physic2D(std::string file, int x = 0, int y = 0, int width = 1, int height = 1);
	~Physic2D();
	virtual void Update();
	virtual void Draw();
};

