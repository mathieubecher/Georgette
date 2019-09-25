#include "pch.h"
#include "Devil.h"
#include "Game.h"

 
Devil::Devil(int x, int y) : Rigidbody("georgette/georgette_idle.spr", x, y, 5, 3),irInBuf(), hStdin(GetStdHandle(STD_INPUT_HANDLE)), coyote(0)
{
	SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT);
}

void Devil::Update() {
		
	if (onfloor) coyote = 0;
	else coyote += Game::Get()->time.getElapsedMs();


	if (GetAsyncKeyState(VK_SPACE))Jump();
	else jumping = false;
	Rigidbody::Update();
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
	if (coyote < COYOTE && !jumping) {
		velocity = JUMP;
		jumping = true;

		return true;
	}
	return false;
}