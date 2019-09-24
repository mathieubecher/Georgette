#include "pch.h"
#include "Devil.h"
#include "Game.h"

Devil::Devil(int x, int y) : Rigidbody("georgette/georgette_idle.spr", x, y, 5, 3)
{
}

void Devil::Update() {
	Rigidbody::Update();
	Move();
	
}
void Devil::Move(bool direction) {
	pos.x += (direction)?SPEED:-SPEED;

	for (auto object : Game::GetObjects()) {
		if (object->id != this->id && object->Collider(this->pos, this->size))
		{
			pos.x -= (direction) ? SPEED : -SPEED;
		}
	}
}