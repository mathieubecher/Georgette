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
}
	this->size = this->sprite.GetSize();
	g->AddChunk(this);
	Game *g = Game::Get();
Map::Map(CHAR_INFO *sprite, int x, int y, int width, int height) : Physic2D(sprite, Vector2(width, height), Vector2f(0, 0)) {
	for (int x = ceil(pos.x); x < ceil(pos.x) + size.x; ++x) {
		for (int y = ceil(pos.y); y < ceil(pos.y) + size.y; ++y) {

			if(x >= this->pos.x && 
				x < this->pos.x + this->size.x && 
				y >= this->pos.y && 
				y < this->pos.y + this->size.y){
				if ((this->sprite.GetCase(x - this->pos.x, y - this->pos.y).Attributes & 0x00f0) == 0) {
						return Box(x,y,1,1);
				}
			}
		}
	}
	return Box();
}
