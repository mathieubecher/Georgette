#pragma once
#include "Windows.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Vector.h"
class SpriteGenerator
{
private:
	static int ReadColorFont(char c);
	static int ReadColorBackground(char c);

public:
	SpriteGenerator();
	~SpriteGenerator();
	static CHAR_INFO *CreateSprite(std::string  fileName, Vector2 *size, Vector2 *pos);
};

