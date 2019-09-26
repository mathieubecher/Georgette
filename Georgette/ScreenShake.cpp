#include "pch.h"
#include "ScreenShake.h"
#include "Game.h"

ScreenShake::ScreenShake():Effect(), time(500),force(1)
{
	pos = Vector2(force, force);
}

ScreenShake::ScreenShake(float time, float force) : Effect(),time(time),force(force) {
	pos = Vector2(force,force);

}


void ScreenShake::Update() {

	Game::Get()->SetPos(Game::Get()->Pos().x + pos.x, Game::Get()->Pos().y + pos.y);
	time -= Game::Get()->time.getElapsedMs();
	//if (time <= 0) delete this;
}