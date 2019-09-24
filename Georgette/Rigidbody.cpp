#include "pch.h"
#include "Rigidbody.h"
#include "Game.h"


Rigidbody::Rigidbody(std::string file, int x, int y, int width, int height) : Collidable(file, x, y, width, height)
{

}
void Rigidbody::Update() {

	velocity += GRAVITY;
	for (auto object : Game::GetObjects()) {
		if (object->id != this->id && object->Collider(pos, size)) velocity = 0;
	}

	pos.y += velocity;
	Collidable::Update();
}
void Rigidbody::SetVelocity(float v) {
	velocity = v;
}