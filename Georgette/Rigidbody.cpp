#include "pch.h"
#include "Rigidbody.h"
#include "Game.h"


Rigidbody::Rigidbody(std::string file, int x, int y, int width, int height, bool includeCircle) : Collidable(file, x, y, width, height,includeCircle),onfloor(false)
{

}
void Rigidbody::Update() {

	velocity += GRAVITY;
	pos.y += velocity * Game::Get()->time.getElapsedMs()*MAXFRAME / 1000.0f;;
	onfloor = false;
	for (auto object : Game::GetObjects()) {
		// test bottom
		if(object->id != this->id){
			Box collide = object->Collider(this->pos,this->size);
			if (velocity >= 0 && collide.width > 0 && collide.height > 0)
			{
				pos.y = collide.y - this->size.y;
				velocity = 0;
				onfloor = true;
			}
			else if (velocity < 0 && collide.width > 0 && collide.height > 0)
			{
			pos.y = collide.y + collide.height;
			velocity = 0.1f;
			}
			
		}
	}

	pos.y += velocity;

	Collidable::Update();
}
void Rigidbody::SetVelocity(float v) {
	velocity = v;
}