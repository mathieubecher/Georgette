#include "pch.h"
#include "People.h"
#include "Game.h"

void People::Update() {
	
	velocity += GRAVITY;
	pos.y += velocity * Game::Get()->time.getElapsedMs()*MAXFRAME / 1000.0f;;
	onfloor = false;
	for (auto object : Game::GetChunks()) {
		// test bottom
		if (object->id != this->id) {
			Box collide = object->Collider(this->pos, this->size);
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
	if (!die) {
		Collidable::Update();
		pos.x += ((direction) ? SPEED : -SPEED) * Game::Get()->time.getElapsedMs()*MAXFRAME / 1000.0f;
		sprite.Case(0, 1)->Char.UnicodeChar = ((int)floor(pos.x) % 2 == 0) ? 'T' : 'X';
		for (auto object : Game::GetChunks()) {
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
		if(countdown <= 0){
			if (Game::Get()->georgette.assshot && Game::Get()->georgette.Collider(this->pos, this->size).width > 0){
				die = true;
				sprite.Case(0, 0)->Attributes = 0x00d0;
				sprite.Case(0, 0)->Char.UnicodeChar = ' ';
				sprite.Case(0, 1)->Attributes = 0x00d4;
				sprite.Case(0, 1)->Char.UnicodeChar = '_';
				timeDelete = 2000;
			}
		}
		else {
			countdown -= Game::Get()->time.getElapsedMs();

		}

	}
	else {
		timeDelete -= Game::Get()->time.getElapsedMs();
		if (timeDelete <= 0) deleteObject = true;
	}
}
People::People(int x, int y): Rigidbody("tile/people.spr",x,y,1,2),die(false),countdown(500){

}
People::~People() {

}
Box People::Collider(Vector2f pos, Vector2 size) {
	return Box();
}
