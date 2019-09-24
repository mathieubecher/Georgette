#include "pch.h"
#include "Physic2D.h"
#include "Game.h"

int Physic2D::ID = 0;

Physic2D::Physic2D() :id(ID++), sprite(), pos(0,0), size(1,1)
{
	Game *g = Game::Get();
	g->AddObject(this);
}
Physic2D::Physic2D(std::string file, int x, int y, int width, int height) : id(ID++), sprite("../resources/sprites/" + file), pos((float)x, (float)y),size((float)width,(float)height)
{
	Game *g = Game::Get();
	g->AddObject(this);

}


void Physic2D::Update() {
	//sprite.TestSpriteSize(this->size);
}

bool Physic2D::Collider(Vector2f pos, Vector2 size) {
	return false;
}

Vector2f Physic2D::GetPos() {
	return pos;
}


void Physic2D::Draw() {
	this->sprite.Draw(Vector2(pos.x,pos.y));
}

Physic2D::~Physic2D()
{
}
