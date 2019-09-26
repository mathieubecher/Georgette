#include "pch.h"
#include "Collidable.h"
#include "Game.h"
Box Collidable::Collider(Vector2f pos, Vector2 size) {
	return (pos.x < this->pos.x + this->size.x &&
		pos.x + size.x > this->pos.x &&
		pos.y < this->pos.y + this->size.y &&
		size.y + pos.y > this->pos.y)? Box(this->pos.x,this->pos.y,this->size.x,this->size.y): Box();
}
Collidable::Collidable(std::string file, int x, int y, int width, int height) : Physic2D(file, x, y, width, height)
{
	Game *g = Game::Get();
	g->AddCollidable(this);
}
Collidable::Collidable() : Physic2D() {
	Game *g = Game::Get();
	g->AddCollidable(this);
}
