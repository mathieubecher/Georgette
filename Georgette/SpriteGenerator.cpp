#include "pch.h"
#include "SpriteGenerator.h"



using namespace std;

SpriteGenerator::SpriteGenerator()
{
}


SpriteGenerator::~SpriteGenerator()
{
}

int SpriteGenerator::ReadColorFont(char c) {
	switch (c) {
	default: return 0x0000; break;
	case '1': return 0x0007; break;
	case '2': return 0x000f; break;
	case 't': return 0x000d; break;
	case 'r': return 0x0004; break;
	}
}
int SpriteGenerator::ReadColorBackground(char c) {
	switch (c) {
	default: return 0x0000; break;
	case '1': return 0x0070; break;
	case '2': return 0x00f0; break;
	case 't': return 0x00d0; break;
	case 'r': return 0x0040; break;
	}
}

CHAR_INFO *SpriteGenerator::CreateSprite(std::string fileName, Vector2 * size, Vector2 *pos = nullptr) {
	ifstream file(fileName);
	file >> size->x;
	file >> size->y;
	if (pos) {
		file >> pos->x;
		file >> pos->y;
	} else {
		int trash = 0;
		file >> trash;
		file >> trash;
	}
	
	CHAR_INFO *res = new CHAR_INFO[size->x*size->y];

	std::string line;
	while (std::getline(file, line, '\0')) {
		int i = 0;
		while (line[i] != '\n') ++i;
		++i;
		int x = 0;
		int y = 0;

		// char
		while(i < line.size() && y < size->y) {
			res[x + y * size->x].Char.UnicodeChar = line[i];
			++i;++x;
			if (line[i] == '\n') { ++i; x = 0; ++y; }
		}

		x = 0; y = 0;
		// color 
		while (i < line.size() && y < size->y) {
			res[x + y * size->x].Attributes = ReadColorFont(line[i]);
			++i; ++x;
			if (line[i] == '\n') {++i; x = 0; ++y;}
		}
		x = 0; y = 0;

		// background
		while (i < line.size() && y < size->y) {
			res[x + y * size->x].Attributes = res[x + y * size->x].Attributes | ReadColorBackground(line[i]);
			++i; ++x;
			if (line[i] == '\n') { ++i; x = 0; ++y; }
		}
	}
	return res;
}