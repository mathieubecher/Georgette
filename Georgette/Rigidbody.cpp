#include "pch.h"
#include "Rigidbody.h"
#include "Game.h"


Rigidbody::Rigidbody(std::string file, int x, int y, int width, int height) : Collidable(file, x, y, width, height),onfloor(false)
{

}
void Rigidbody::Update() {

	velocity += GRAVITY;
	pos.y += velocity;
	onfloor = false;
	for (auto object : Game::GetObjects()) {
		// test bottom
		if (velocity > 0 && object->id != this->id && object->Collider(Vector2f(this->pos.x, this->pos.y + this->size.y - 1), Vector2(this->size.x, 1)))
		{
			if(velocity <=1)pos.y = floor(pos.y);
			else pos.y = ceil(pos.y - velocity);
			velocity = 0;
			onfloor = true;
		}
		else {
			//test top
			if (velocity < 0 && object->id != this->id && object->Collider(Vector2f(this->pos.x, this->pos.y), Vector2(this->size.x, 1)))
			{
			pos.y = floor(pos.y-velocity) ;
			velocity = 0.2f;
			}
		}
	}

	pos.y += velocity;

	Collidable::Update();
}
void Rigidbody::SetVelocity(float v) {
	velocity = v;
}