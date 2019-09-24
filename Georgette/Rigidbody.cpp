#include "pch.h"
#include "Rigidbody.h"


void Rigidbody::Update() {

	Collidable::Update();
}
Rigidbody::Rigidbody(std::string file, int x, int y, int width, int height) : Collidable(file, x, y, width, height)
{

}