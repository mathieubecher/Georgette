#include "pch.h"
#include "Rigidbody.h"



Rigidbody::Rigidbody(std::string file, int x, int y, int width, int height) : Collidable(file, x, y, width, height)
{

}
void Rigidbody::Update() {

	velocity += GRAVITY;
	

	pos.y += velocity;
	Collidable::Update();
}
void Rigidbody::SetVelocity(float v) {
	velocity = v;
}