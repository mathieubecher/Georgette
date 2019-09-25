#include "pch.h"
#include "Devil.h"
#include "Game.h"

 
Devil::Devil(int x, int y) : Rigidbody("georgette/georgette_idle.spr", x, y, 5, 3),coyote(0.0f), assshot(false), jumping(false)
{
}

void Devil::Update() {
		
	if (onfloor) coyote = 0;
	else coyote += Game::Get()->time.getElapsedMs();


	if (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(0x5A) || GetAsyncKeyState(VK_UP))Jump();
	else jumping = false;

	if (assshot) velocity = 1;
	Rigidbody::Update();
	if (onfloor && assshot) assshot = false;
	
	if(!assshot){
		if (GetAsyncKeyState(0x51) || GetAsyncKeyState(VK_LEFT))Move(false);
		else if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))Move();
	}

	if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) AssShot();
	
	
	Game::Get()->SetPos(floor(this->pos.x - SCREEN_WIDTH / 2), floor(this->pos.y - SCREEN_HEIGHT / 2));
}


void Devil::Move(bool direction) {
	pos.x += (direction)?SPEED:-SPEED;

	for (auto object : Game::GetObjects()) {
		if (object->id != this->id)
		{
			Box collide = object->Collider(this->pos, this->size);
			if (collide.width > 0 && collide.height > 0) {
				if (direction) pos.x = collide.x - this->size.x;
				else pos.x = collide.x + collide.width;
			}
		}
	}
}

void Devil::AssShot() {
	if (!onfloor && !assshot) {
		assshot = true;
		jumping = false;
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