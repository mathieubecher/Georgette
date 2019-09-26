#include "pch.h"
#include "Devil.h"
#include "Game.h"
 
Devil::Devil(int x, int y) : Rigidbody("georgette/georgette_idle.spr", x, y, 5, 3),coyote(0.0f), assshot(false), assshotScore(0), jumping(false), asshotinputpress(false)
{
}

void Devil::Update() {
	if (assshot){
		UpdateAssShot();
	}
	else {
		if (onfloor) coyote = 0;
		else coyote += Game::Get()->time.getElapsedMs();
		if (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(0x5A) || GetAsyncKeyState(VK_UP))Jump();
		else jumping = false;

		Rigidbody::Update();

		if (GetAsyncKeyState(0x51) || GetAsyncKeyState(VK_LEFT))Move(false);
		else if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))Move();

		if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) AssShot();
		else asshotinputpress = false;
	}
	
	Game::Get()->SetPos(floor(this->pos.x - SCREEN_WIDTH / 2), floor(this->pos.y - SCREEN_HEIGHT / 2));
}


void Devil::Move(bool direction) {
	pos.x += ((direction)?SPEED:-SPEED) * Game::Get()->time.getElapsedMs()*MAXFRAME/1000.0f;

	for (auto object : Game::GetObjects()) {
		if (object->id != this->id)
		{
			Box collide = object->Collider(Vector2f(this->pos.x,(velocity>0)?(int)floor(this->pos.y): ceil(this->pos.y)), this->size);
			if (collide.width > 0 && collide.height > 0) {
				if (direction) pos.x = collide.x - this->size.x;
				else pos.x = collide.x + collide.width;
			}
		}
	}
}

void Devil::AssShot() {
	if(!asshotinputpress){
		asshotinputpress = true;
		if (!onfloor && !assshot) {

			Wait(200);
			assshotScore = 0.5f;
			this->pos.x = floor(this->pos.x);
			this->pos.y = floor(this->pos.y);
			assshot = true;
			jumping = false;
		}
	}
}



void Devil::UpdateAssShot(){
	velocity = 1;
	assshotScore += (assshotScore > 5)?1.42f: 0.5f;
	pos.y += velocity;
	
	std::list<CHAR_INFO*> cases;
	// Destruct case
	for (auto chunk : Game::GetChunks()) {
		
		std::list<CHAR_INFO*> caseschunk = chunk->CollideCase(this->pos,this->size);
		cases.insert(cases.end(),caseschunk.begin(),caseschunk.end());
	}
	// Get break indicator
	int maxForce = 1;
	float indicator = 0;
	for (auto breakcase : cases) {
		if ((breakcase->Attributes & 0x00f0) == 0) {
			indicator += 1 - Map::CharToBreakIndicator(breakcase->Char.UnicodeChar);
		}
	}
	if (indicator > 0) {
		assshotScore -= indicator;
		Game::Get()->ScreenShake(100, 1);
	}
	float destruct = 0;
	if (assshotScore >= 0) destruct = 1;
	else destruct = (assshotScore + indicator) / indicator;

	int nbdestroy = 0;
	for (auto breakcase : cases) {
		if ((breakcase->Attributes & 0x00f0) == 0x00f0)
		{
			breakcase->Char.UnicodeChar = ' ';
			breakcase->Attributes = 0x00f0;
			++nbdestroy;
		}
		else {
			float actualValue = Map::CharToBreakIndicator(breakcase->Char.UnicodeChar);
			if (actualValue + destruct < 1)
				breakcase->Char.UnicodeChar = Map::BreakIndicatorToChar(actualValue + destruct);
			else {
				breakcase->Attributes = 0x00f0;
				breakcase->Char.UnicodeChar = ' ';
				++nbdestroy;
			}

		}
	}
	if (assshotScore <= 0) {
		assshot = false;
		Game::Get()->ScreenShake(100, 2);
		if(nbdestroy < cases.size()) this->pos.y = floor(this->pos.y - velocity);
		else this->pos.y = floor(this->pos.y);
		velocity = 0;
		
		Game::Get()->Wait(50);
		//Rigidbody::Update();
		onfloor = true;
	}
	
}

bool Devil::Jump() {
	if (coyote < COYOTE && !jumping) {
		velocity = JUMP;
		jumping = true;

		return true;
	}
	return false;
}