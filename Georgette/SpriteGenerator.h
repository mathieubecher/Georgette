#pragma once
#include "Windows.h"
class SpriteGenerator
{
private:
	int ReadColor(char c);

public:
	SpriteGenerator();
	~SpriteGenerator();
	CHAR_INFO *CreateSprite(std::string fileName);
};

