#include "pch.h"
#include "Map.h"
#include "Game.h"
#include <math.h>
Map::Map(std::string file, int x, int y, int width, int height) : Physic2D(file,x,y,width,height)
{
	Game *g = Game::Get();
	g->AddChunk(this);
}
bool Map::Collider(Vector2f pos, Vector2 size) {
	for (int x = floor(pos.x); x < floor(pos.x) + size.x; ++x) {
		for (int y = floor(pos.y); y < floor(pos.y) + size.y; ++y) {
			if(x >= this->pos.x && x < this->pos.x + this->size.x && y >= this->pos.y && y < this->pos.y + this->size.y){

				if (this->sprite.GetCase(x - this->pos.x, y - this->pos.y).Attributes & 0x00f0 == 0x0000) {
					return true;
				}
			}
		}
	}
	return false;
}
