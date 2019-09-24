#pragma once
#include "Windows.h"
#include <stdio.h>
#include <iostream>
#include "NYTimer.h"
#include"Vector.h"
#include"SpriteGenerator.h"

class Sprite
{
private:
	Vector2 size;
	Vector2 pos;
	CHAR_INFO * sprite;
public:
	void TestSpriteSize(Vector2 const &sizehitbox);
	Sprite();
	Sprite(std::string file);
	Sprite(int x, int y);
	Sprite(CHAR_INFO *sprite, Vector2 size);
	Vector2 GetSize();
	void SetSize(int x, int y);

	virtual void Instantiate();
	virtual void Draw(Vector2 pos);
	CHAR_INFO *GetSprite();
	CHAR_INFO GetCase(int x, int y);

	~Sprite();
};

