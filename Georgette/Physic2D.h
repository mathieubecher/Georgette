#pragma once
#include "Sprite.h"
#include "Vector.h"
class Physic2D
{
protected:
	Sprite sprite;
	Vector2f pos;
	Vector2 size;
	static int ID;

public:
	float wait;
	const int id;
	Physic2D(bool includeCircle = true);
	Physic2D(std::string file, int x = 0, int y = 0, int width = 1, int height = 1,bool includeCircle= true);
	Physic2D(CHAR_INFO *sprite, Vector2 size, Vector2f pos);
	~Physic2D();
	virtual Box Collider(Vector2f pos, Vector2 size);
	virtual void Update();
	virtual void Draw();
	Vector2f GetPos();
	Sprite *GetSprite();
	void Wait(float wait);
};

