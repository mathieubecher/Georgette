#pragma once
#include "Sprite.h"
class Physic2D
{
protected:
	Sprite sprite;
	Vector2f pos;
	Vector2 size;
	static int ID;
public:
	const int id;
	Physic2D();
	Physic2D(std::string file, int x = 0, int y = 0, int width = 1, int height = 1);
	Physic2D(CHAR_INFO *sprite, Vector2 size, Vector2f pos);
	~Physic2D();
	virtual bool Collider(Vector2f pos, Vector2 size);
	virtual void Update();
	virtual void Draw();
	Vector2f GetPos();
};

