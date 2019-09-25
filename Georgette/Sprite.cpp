#include "pch.h"
#include "Sprite.h"
#include "Game.h"
#include <math.h>

Sprite::Sprite()
{
	this->pos.x = 0;
	this->pos.y = 0;
	this->size.x = 1;
	this->size.y = 1;
	Instantiate();
		
	sprite[0].Char.UnicodeChar = '#';
	sprite[0].Attributes = 0x00f0;
}

Sprite::Sprite(std::string file) {
	this->pos.x = 0;
	this->pos.y = 0;
	this->sprite = SpriteGenerator::CreateSprite(file,&this->size,&this->pos);
}

Sprite::Sprite(CHAR_INFO *sprite, Vector2 size) {
	this->sprite = sprite;
	this->size = size;
	this->pos = Vector2(0,0);
}

CHAR_INFO *Sprite::GetSprite() {
	return sprite;
}

Sprite::Sprite(int x,int y)
{
	this->pos.x = 0;
	this->pos.y = 0;
	this->size.x = x;
	this->size.y = y;
	Instantiate();
}

void Sprite::SetSize(int x, int y) {
	size.x = x;
	size.y = y;
}

Vector2 Sprite::GetSize() {
	return size;
}

Sprite::~Sprite()
{
	delete [] sprite;
}

void Sprite::Instantiate() {
	sprite = new CHAR_INFO[this->size.x*this->size.y];
}
void Sprite::Draw(Vector2 pos) {
	Game *g = Game::Get();
	CHAR_INFO * buffer = g->Buffer();

	for (int x = 0; x < this->size.x; ++x) {
		for (int y = 0; y < this->size.y; ++y) {


			int posx = floor(pos.x) + this->pos.x + x - g->Pos().x;
			int posy = floor(pos.y)  + this->pos.y + y - g->Pos().y;

			if (posx >= 0 && posx < SCREEN_WIDTH && posy >= 0 && posy < SCREEN_HEIGHT){
				CHAR_INFO poscase = this->GetCase(x,y);
				if (poscase.Char.AsciiChar != ' ' || (poscase.Attributes & 0x00f0) != 0x00d0) {
					buffer[posx + posy * SCREEN_WIDTH].Char.UnicodeChar = poscase.Char.UnicodeChar;

					if ((poscase.Attributes & 0x00f0) != 0x00d0) buffer[posx + posy * SCREEN_WIDTH].Attributes = poscase.Attributes;
					else
					{
						int bg = (buffer[posx + posy * SCREEN_WIDTH].Attributes & 0x00f0);
						int color = (poscase.Attributes & 0x000f);
						int bgcolor = bg | color;
						buffer[posx + posy * SCREEN_WIDTH].Attributes = bgcolor ;	
					}
				}
			}
		}
	}
}
CHAR_INFO Sprite::GetCase(int x, int y) {
	return this->sprite[x + y * this->size.x];
}
CHAR_INFO *Sprite::Case(int x, int y) {
	return &this->sprite[x + y * this->size.x];
}
void Sprite::TestSpriteSize(Vector2 const &sizehitbox) {
	for (int x = -this->pos.x; x < -this->pos.x + sizehitbox.x; ++x) {
		for (int y = -this->pos.y; y < -this->pos.y + sizehitbox.y; ++y) {
			this->sprite[x + y * this->size.x].Attributes = 0x000f;
			this->sprite[x + y * this->size.x].Char.UnicodeChar = '.';
		}
	}
}