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
	Vector2 pos;
	Vector2 size;
	CHAR_INFO * sprite;
public:
	Sprite();
	Sprite(std::string file);
	Sprite(int x, int y);
	Vector2 GetSize();
	void SetSize(int x, int y);
	void SetPos(int x, int y);

	virtual void Instantiate();
	virtual void Draw();

	CHAR_INFO GetCase(int x, int y);

	~Sprite();
};

