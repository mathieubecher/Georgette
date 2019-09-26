#include "pch.h"
#include "Map.h"
#include "Game.h"
#include <math.h>

Map::Map(std::string file, int x, int y, int width, int height) : Physic2D(file,x,y,width,height)
{
	Game *g = Game::Get();
	g->AddChunk(this);
	this->size = this->sprite.GetSize();
}

Box Map::Collider(Vector2f pos, Vector2 size) {
	if(!sprite.clipped){
		for (int x = floor(pos.x); x < ceil(pos.x) + size.x; ++x) {
			for (int y = floor(pos.y); y < ceil(pos.y) + size.y; ++y) {

				if (x >= (this->pos.x) &&
					x < (this->pos.x) + this->size.x &&
					y >= (this->pos.y) &&
					y < (this->pos.y) + this->size.y) {
					if ((this->sprite.GetCase(x - (this->pos.x), y - (this->pos.y)).Attributes & 0x00f0) == 0) {
						return Box(x, y, 1, 1);
					}
				}
			}
		}
	}
	return Box();
}

std::list<CHAR_INFO*> Map::CollideCase(Vector2f pos, Vector2 size) {
	std::list<CHAR_INFO*> collideCase;
	if (!sprite.clipped) {
		for (int x = floor(pos.x); x < ceil(pos.x) + size.x; ++x) {
			for (int y = floor(pos.y); y < ceil(pos.y) + size.y; ++y) {

				if (x >= this->pos.x &&
					x < this->pos.x + this->size.x &&
					y >= this->pos.y &&
					y < this->pos.y + this->size.y) {
					if ((this->sprite.GetCase(x - this->pos.x, y - this->pos.y).Attributes & 0x00f0) == 0 || (this->sprite.GetCase(x - this->pos.x, y - this->pos.y).Char.UnicodeChar != ' ')) {
						collideCase.push_back(this->sprite.Case(x - this->pos.x, y - this->pos.y));
						if ((this->sprite.GetCase(x - this->pos.x, y - this->pos.y).Attributes & 0x00f0) == 0)
							casesSave.push_back(CaseSave(x - this->pos.x, y - this->pos.y, this->sprite.Case(x - this->pos.x, y - this->pos.y)->Char.UnicodeChar));
					}
				}
			}
		}
	}
	return collideCase;
}

void Map::Update() {
	Physic2D::Update();
	while (casesSave.size() > 0) {
		ActionCase(casesSave.front());
		casesSave.pop_front();
	}
}
void Map::ActionCase(CaseSave c) {
	float value = ((sprite.GetCase(c.x, c.y).Char.UnicodeChar == ' ') ? 1: CharToBreakIndicator(sprite.GetCase(c.x, c.y).Char.UnicodeChar)) -CharToBreakIndicator(c.c);
	float neigbourgforce = value / 2;
	if (neigbourgforce > 0.2f) {
		if ((c.x + 1 >= 0 && c.x + 1 < size.x) && (sprite.GetCase(c.x + 1, c.y).Attributes & 0x00f0) == 0) AddForce(*sprite.Case(c.x + 1, c.y), neigbourgforce);
		if ((c.x - 1 >= 0 && c.x - 1 < size.x) && (sprite.GetCase(c.x - 1, c.y).Attributes & 0x00f0) == 0)AddForce(*sprite.Case(c.x - 1, c.y), neigbourgforce);
		if ((c.y + 1 >= 0 && c.y + 1 < size.y) && (sprite.GetCase(c.x, c.y +1).Attributes & 0x00f0) == 0) AddForce(*sprite.Case(c.x, c.y + 1), neigbourgforce);
		if ((c.y - 1 >= 0 && c.y - 1 < size.y) && (sprite.GetCase(c.x, c.y-1).Attributes & 0x00f0) == 0) AddForce(*sprite.Case(c.x, c.y - 1), neigbourgforce);
	}
}
void Map::AddForce(CHAR_INFO & c, float force) {
	c.Char.UnicodeChar = BreakIndicatorToChar(force + CharToBreakIndicator(c.Char.UnicodeChar));
	if (c.Char.UnicodeChar == '.') {
		c.Attributes = 0x00d0;
		c.Char.UnicodeChar = ' ';
	}
}

Map::Map(CHAR_INFO *sprite, int x, int y, int width, int height) : Physic2D(sprite, Vector2(width, height), Vector2f((float)x, (float)y)) {
	Game *g = Game::Get();
	g->AddChunk(this);
	this->size = this->sprite.GetSize();
}

float Map::CharToBreakIndicator(char c) {
	switch (c) {
	default:
		return 0;
		break;
	case '*':
		return 0.2f;
		break;
	case 'x':
		return 0.4f;
		break;
	case '/':
		return 0.6f;
		break;
	case 'X':
		return 0.8f;
		break;
	}
	return 1;
}

char Map::BreakIndicatorToChar(float i) {
	if (i == 0.2f) return ' ';
	else if (i <= 0.4f) return '*';
	else if (i <= 0.6f) return 'x';
	else if (i <= 0.8f) return '/';
	else if (i <= 1) return 'X';
	else return '.';
}
