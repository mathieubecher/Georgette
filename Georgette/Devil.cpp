#include "pch.h"
#include "Devil.h"
#include "Game.h"

 
Devil::Devil(int x, int y) : Rigidbody("georgette/georgette_idle.spr", x, y, 5, 3),coyote(0.0f), assshot(false), assshotScore(0), jumping(false)
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
	}
	
	Game::Get()->SetPos(floor(this->pos.x - SCREEN_WIDTH / 2), floor(this->pos.y - SCREEN_HEIGHT / 2));
}


void Devil::Move(bool direction) {
	pos.x += (direction)?SPEED:-SPEED;

	for (auto object : Game::GetObjects()) {
		if (object->id != this->id)
		{
			Box collide = object->Collider(this->pos, this->size);
			if (collide.width > 0 && collide.height > 0) {
				if (direction) pos.x = collide.x - this->size.x;
				else pos.x = ceil(collide.x + collide.width);
			}
		}
	}
}

void Devil::AssShot() {
	if (!onfloor && !assshot) {
		assshotScore = 0.5f;
		this->pos.x = floor(this->pos.x);
		this->pos.y = floor(this->pos.y);
		assshot = true;
		jumping = false;
	}
}

float Devil::CharToBreakIndicator(char c) {
	switch (c) {
	default:
		return 0;
		break;
	case '*':
		return 0.2f;
		break;
	case 'x':
		return 0.4f;
		break;
	case '/':
		return 0.6f;
		break;
	case 'X':
		return 0.8f;
		break;
	}
	return 0;
}
char Devil::BreakIndicatorToChar(float i) {
	if (i == 0.2f) return ' ';
	else if (i <= 0.4f) return '*';
	else if (i <= 0.6f) return 'x';
	else if (i <= 0.8f) return '/';
	else if (i <= 1) return 'X';
}


void Devil::UpdateAssShot(){
	velocity = 1;
	assshotScore += (assshotScore > 5)?1: 0.5f;
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
			indicator += 1 - CharToBreakIndicator(breakcase->Char.UnicodeChar);
		}
	}
	if (indicator > 0) {
		assshotScore -= indicator;
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
			float actualValue = CharToBreakIndicator(breakcase->Char.UnicodeChar);
			if (actualValue + destruct < 1)
				breakcase->Char.UnicodeChar = BreakIndicatorToChar(actualValue + destruct);
			else {
				breakcase->Attributes = 0x00f0;
				breakcase->Char.UnicodeChar = ' ';
				++nbdestroy;
			}

		}
	}
	if (assshotScore <= 0) {
		//this->pos.y = this->pos.y - velocity + 0.1f;
		assshot = false;
		pos.y -= velocity;
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