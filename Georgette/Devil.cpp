#include "pch.h"
#include "Devil.h"
#include "Game.h"

 
Devil::Devil(int x, int y) : Rigidbody("georgette/georgette_idle.spr", x, y, 5, 3),irInBuf(), hStdin(GetStdHandle(STD_INPUT_HANDLE))
{
	SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT);
}

void Devil::Update() {
	Rigidbody::Update();	

	if (GetAsyncKeyState(VK_SPACE))Jump();
	if (GetAsyncKeyState(0x51))Move(false);
	else if (GetAsyncKeyState(0x44))Move();

	
	Game::Get()->SetPos(floor(this->pos.x - SCREEN_WIDTH / 2), floor(this->pos.y - SCREEN_HEIGHT / 2));
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
bool Devil::Jump() {
	if (onfloor) {
		velocity = JUMP;
		
		return true;
	}
	return false;
}