#include "pch.h"
#include "Sprite.h"
#include "Game.h"

Sprite::Sprite()
{
	this->size.x = 1;
	this->size.y = 1;
	Instantiate();
}

Sprite::Sprite(std::string file) {
	this->size.x = 1;
	this->size.y = 1;
	
	Instantiate();

	
}
Sprite::Sprite(int x,int y)
{
	this->size.x = x;
	this->size.y = y;
	Instantiate();

	sprite[0].Char.UnicodeChar = '#';
	sprite[0].Attributes = 0x0081;
}

Sprite::~Sprite()
{
	delete [] sprite;
}

void Sprite::Instantiate() {
	this->pos.x = 5;
	this->pos.y = 5;
	sprite = new CHAR_INFO[this->size.x*this->size.y];
}
void Sprite::Draw() {
	Game *g = Game::Get();
	CHAR_INFO * buffer = g->Buffer();

	for (int x = 0; x < this->size.x; ++x) {
		for (int y = 0; y < this->size.y; ++y) {


			int posx = this->pos.x + x;
			int posy = this->pos.y + y;

			CHAR_INFO poscase = this->GetCase(x,y);
			if (poscase.Char.AsciiChar != ' ') {
				buffer[posx + posy * SCREEN_WIDTH].Char.UnicodeChar = poscase.Char.UnicodeChar;
				buffer[posx + posy * SCREEN_WIDTH].Attributes = poscase.Attributes;
			}

		}
	}
}
CHAR_INFO Sprite::GetCase(int x, int y) {
	return this->sprite[x + y * this->size.x];
}