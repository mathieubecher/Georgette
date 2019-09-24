#include "pch.h"
#include "Collidable.h"

bool Collidable::Collider(Vector2f pos, Vector2 size) {
	return pos.x < this->pos.x + this->size.x &&
		pos.x + size.x > this->pos.x &&
		pos.y < this->pos.y + this->size.y &&
		size.y + pos.y > this->pos.y;
}
