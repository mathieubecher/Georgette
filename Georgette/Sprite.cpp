#include "pch.h"
#include "Sprite.h"
#include "Game.h"


Sprite::Sprite()
{
	this->size.x = 1;
	this->size.y = 1;
	Instantiate();
		
	sprite[0].Char.UnicodeChar = '#';
	sprite[0].Attributes = 0x00f0;
}

Sprite::Sprite(std::string file) {
	this->sprite = SpriteGenerator::CreateSprite(file,&this->size);
	this->pos.x = 10;
	this->pos.y = 5;
}
Sprite::Sprite(int x,int y)
{
	this->size.x = x;
	this->size.y = y;
	Instantiate();

}

void Sprite::SetSize(int x, int y) {
	size.x = x;
	size.y = y;
}
void Sprite::SetPos(int x, int y) {
	pos.x = x;
	pos.y = y;
}
Vector2 Sprite::GetSize() {
	return size;
}

Sprite::~Sprite()
{
	delete [] sprite;
}

void Sprite::Instantiate() {
	this->pos.x = 0;
	this->pos.y = 0;
	sprite = new CHAR_INFO[this->size.x*this->size.y];
}
void Sprite::Draw() {
	Game *g = Game::Get();
	CHAR_INFO * buffer = g->Buffer();

	for (int x = 0; x < this->size.x; ++x) {
		for (int y = 0; y < this->size.y; ++y) {


			int posx = this->pos.x + x - g->Pos().x;
			int posy = this->pos.y + y - g->Pos().y;

			if (posx >= 0 && posx < SCREEN_WIDTH && posy >= 0 && posy < SCREEN_HEIGHT){
				CHAR_INFO poscase = this->GetCase(x,y);
				if (poscase.Char.AsciiChar != ' ') {
					buffer[posx + posy * SCREEN_WIDTH].Char.UnicodeChar = poscase.Char.UnicodeChar;
					buffer[posx + posy * SCREEN_WIDTH].Attributes = poscase.Attributes;
				}
			}
		}
	}
}
CHAR_INFO Sprite::GetCase(int x, int y) {
	return this->sprite[x + y * this->size.x];
}