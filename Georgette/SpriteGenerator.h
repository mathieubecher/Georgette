#pragma once
#include "Windows.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

class SpriteGenerator
{
private:
	int ReadColor(char c);

public:
	SpriteGenerator();
	~SpriteGenerator();
	CHAR_INFO *CreateSprite(std::string  fileName);
};

