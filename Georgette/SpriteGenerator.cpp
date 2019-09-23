#include "pch.h"
#include "SpriteGenerator.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>


using namespace std;

SpriteGenerator::SpriteGenerator()
{
}


SpriteGenerator::~SpriteGenerator()
{
}

int SpriteGenerator::ReadColor(char c) {
	switch (c) {
	case '.': {
		return 0x66;
	}
	case '0': {
		return 0x00;
	}
	case '3': {
		return 0xFF;
	}
	}
	return 0x00;
}

/**
 * Create the CHAR_INFO array from the specified file
 * For the moment, doesn't handle animations
 *
 *
*/
CHAR_INFO *SpriteGenerator::CreateSprite(std::string fileName) {
	ifstream file(fileName);
	int x;
	int y;
	char curr;
	file >> x;
	file >> y;
	if (file.fail()) return nullptr;
	CHAR_INFO *res = new CHAR_INFO[x*y];
	do {
		file >> curr;
	} while (curr != '\n');
	for (size_t i = 0; i < x; ++i) {
		for (size_t j = 0; j < y; ++j) {
			file >> curr;
			if (file.fail()) return nullptr;
			res[i*j].Char.AsciiChar = curr;
		}
		file >> curr;
	}
	for (size_t i = 0; i < x; ++i) {
		for (size_t j = 0; j < y; ++j) {
			file >> curr;
			if (file.fail()) return nullptr;
			res[i*j].Attributes = ReadColor(curr);
		}
		file >> curr;
	}
	//TODO Reste à gérer le contour en plus de la couleur de fonte
	/*
	for (size_t i = 0; i < x; ++i) {
		for (size_t j = 0; j < y; ++j) {
			file >> curr;
			if (file.fail()) return nullptr;
			res[i*j].Attributes = ReadColor(curr);
		}
		file >> curr;
	}*/
	return res;
}