#include "pch.h"
#include "Physic2D.h"
#include "Game.h"
#include <math.h>
int Physic2D::ID = 0;

Physic2D::Physic2D(bool includeCircle) :id(ID++), sprite(), pos(6,14), size(1,1)
{
	if(includeCircle){
		Game *g = Game::Get();
		g->AddObject(this);
	}
}
Physic2D::Physic2D(std::string file, int x, int y, int width, int height, bool includeCircle) : id(ID++), sprite("../resources/sprites/" + file), pos((float)x, (float)y), size((float)width, (float)height)
{
	if(includeCircle){
		Game *g = Game::Get();
		g->AddObject(this);
	}
	
}

Physic2D::Physic2D(CHAR_INFO *sprite, Vector2 size, Vector2f pos) : id(ID++), sprite(sprite, size), pos(pos), size(size)
{
	Game *g = Game::Get();
	g->AddObject(this);
}


void Physic2D::Update() {
}

Box Physic2D::Collider(Vector2f pos, Vector2 size) {
	return Box();
}

Vector2f Physic2D::GetPos() {
	return pos;
}


void Physic2D::Draw() {
	this->sprite.Draw(Vector2(floor(pos.x),floor(pos.y)));
}

Physic2D::~Physic2D()
{
}


Sprite *Physic2D::GetSprite() {
	return &sprite;
}
void Physic2D::Wait(float wait) {
	this->wait = wait;
}