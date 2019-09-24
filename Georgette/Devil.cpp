#include "pch.h"
#include "Devil.h"
#include "Game.h"

Devil::Devil(int x, int y) : Rigidbody("georgette/georgette_idle.spr", x, y, 5, 3)
{
}

void Devil::Update() {
	Rigidbody::Update();
	Move();
	Jump();
}
void Devil::Move(bool direction) {
	pos.x += (direction)?SPEED:-SPEED;

	for (auto object : Game::GetObjects()) {
		if (object->id != this->id && object->Collider(this->pos, this->size))
		{
			pos.x -= (direction) ? SPEED : -SPEED;
		}
	}

	Game::Get()->SetPos(floor(this->pos.x - SCREEN_WIDTH/2),floor(this->pos.y - SCREEN_HEIGHT/ 2));

}
bool Devil::Jump() {
	if (onfloor) {
		velocity = JUMP;
		return true;
	}
	return false;
}