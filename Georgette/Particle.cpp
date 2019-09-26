#include "pch.h"
#include "Particle.h"
#include "Game.h"

Particle::Particle(int x, int y):Collidable("tile/particle.spr",x,y,1,1,true),timeDelete(1000),value(1)
{
}

void Particle::Update() {
	timeDelete -= Game::Get()->time.getElapsedMs();
	pos.y-=(float)(rand()%50)/200.0f;
	if (rand() % 2 == 1)pos.x += (rand() % 2 == 0) ? (float)(rand() % 50) / 50.0f :-(float)(rand() % 50) / 50.0f;
	if (timeDelete <= 0) deleteObject = true;
	value -= (float)(rand() % 2) /20.0f;

	if (value <= 0.1f) this->sprite.Case(0,0)->Char.UnicodeChar = '\'';
	else if (value <= 0.2f) this->sprite.Case(0, 0)->Char.UnicodeChar = '"';
	else if (value <= 0.3f) this->sprite.Case(0, 0)->Char.UnicodeChar = 'o';
	else if (value <= 0.4f) this->sprite.Case(0, 0)->Char.UnicodeChar = 'x';
	else if (value <= 0.6f) this->sprite.Case(0, 0)->Char.UnicodeChar = 'X';
	else if (value <= 0.8f) this->sprite.Case(0, 0)->Char.UnicodeChar = 'O';
}
void Particle::Draw() {
	Physic2D::Draw();
}
Box Particle::Collider(Vector2f pos, Vector2 size) {
	return Box();
}