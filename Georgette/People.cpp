#include "pch.h"
#include "People.h"
#include "Game.h"

void People::Update() {
	Rigidbody::Update();
	pos.x += ((direction) ? SPEED : -SPEED) * Game::Get()->time.getElapsedMs()*MAXFRAME / 1000.0f;
	sprite.Case(0, 1)->Char.UnicodeChar = ((int)floor(pos.x)%2 == 0)?'T':'X';
	for (auto object : Game::GetObjects()) {
		if (object->id != this->id)
		{
			Box collide = object->Collider(Vector2f(this->pos.x, (velocity > 0) ? (int)floor(this->pos.y) : ceil(this->pos.y)), this->size);
			if (collide.width > 0 && collide.height > 0) {
				if (direction) pos.x = collide.x - this->size.x;
				else pos.x = collide.x + collide.width;
				direction = !direction;
			}
		}
	}
}
People::People(int x, int y): Rigidbody("tile/people.spr",x,y,1,2){

}
People::~People() {

}
Box People::Collider(Vector2f pos, Vector2 size) {
	return Box();
}

std::list<CHAR_INFO*> People::CollideCase(Vector2f pos, Vector2 size) {
	return std::list<CHAR_INFO*>();
}