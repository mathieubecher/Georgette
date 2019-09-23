#include "pch.h"
#include "Physics2D.h"
#include "Game.h"

Physics2D::Physics2D()
{
	this->size.x = 1;
	this->size.y = 1;
	Instantiate();
}

Physics2D::Physics2D(std::string file) {
	this->size.x = 1;
	this->size.y = 1;
	Instantiate();
}
Physics2D::Physics2D(Vector2 size)
{
	this->size = size;
	this->pos.x = 0;
	this->pos.y = 0;
	sprite = new CHAR_INFO[this->size.x*this->size.y];

	sprite[0].Char.AsciiChar = '#';
	sprite[0].Attributes = 0x0E;
	sprite[0].Char.UnicodeChar = 0x0E;
}
Physics2D::Physics2D(int x,int y)
{
	this->size.x = x;
	this->size.y = y;
	Instantiate();
}

Physics2D::~Physics2D()
{
	delete [] sprite;
}

void Physics2D::Instantiate() {
	this->pos.x = 0;
	this->pos.y = 0;
	sprite = new CHAR_INFO[this->size.x*this->size.y];

	sprite[0].Char.AsciiChar = '#';
	sprite[0].Attributes = 0x0E;
}
void Physics2D::Update() {

} 

void Physics2D::Draw() {
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
CHAR_INFO Physics2D::GetCase(int x, int y) {
	return this->sprite[x + y * this->size.x];
}