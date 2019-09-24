#include "pch.h"
#include "Physic2D.h"
#include "Game.h"

Physic2D::Physic2D() :sprite(), pos(0,0), size(1,1)
{
	Game *g = Game::Get();
	g->AddObject(this);
}
Physic2D::Physic2D(std::string file, int x, int y, int width, int height) : sprite("../resources/sprites/georgette/" + file), pos((float)x, (float)y),size((float)width,(float)height)
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



void Physic2D::Draw() {
	this->sprite.Draw(Vector2(pos.x,pos.y));
}

Physic2D::~Physic2D()
{
}
