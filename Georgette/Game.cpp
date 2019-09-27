#include "pch.h"
#include "Game.h"
#include "Hi.h"
#include "Map.h"
#include "Rigidbody.h"
#include "Collidable.h"
#include "Devil.h"
#include "MapGenerator.h"
#include <stdlib.h>
#include <time.h>
#include <cstdbool>
#include <sstream>
#include "People.h"

CHAR_INFO * Game::Buffer() {
	return *this->buffer;
}
Vector2 Game::Pos() {
	return Vector2(this->pos.x + this->posChange.x,this->pos.y + this->posChange.y);
} 
Vector2 Game::RealPos() {
	return pos;
}
void Game::SetPos(int x, int y) {
	pos.x = x;
	pos.y = y;
}

Game * Game::Get() {
	static Game game;
	return &game;
}

Game::Game() : hOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE)), i(0), pos(0,0), georgette(0,0), background("../resources/sprites/tile/background.spr"), title("../resources/sprites/tile/title.spr")
{
	time.getElapsedMs(true);
}
void Game::Init() {
	
	
	georgette.Init(0, 0);
	score = 0;
	chunks.clear();
	while (objects.size() > 0) {
		chunks.remove((Map*)objects.front());
		collidables.remove((Collidable*)objects.front());
		delete objects.front();
		objects.remove(objects.front());
	}
	chunks.clear();
	collidables.clear();
	objects.clear();
}

void Game::Run() {
	//MapGenerator::GenerateFirstChunk();
	bool exit = false;
	while(!exit){
		bool init = false;
		DrawMenu();
		if (GetAsyncKeyState(VK_RETURN))init = true;
		if(init){
			Init();
			bool escape = false;
			while (!escape) {
				if (time.getElapsedMs() > 1000.0f / MAXFRAME) {

					if (time.getElapsedMs() >= wait) Update();
					else wait -= time.getElapsedMs();
					Draw();
					if (screenshake < 0) {
						posChange.x = 0;
						posChange.y = 0;
					}
					else screenshake -= time.getElapsedMs();
					time.getElapsedMs(true);
					if (GetAsyncKeyState(VK_ESCAPE))escape = true;
				}
			}
			
		}
	}
}
Game::~Game()
{
	for (auto i : chunks) {
		delete(i);
	}
}

void Game::Update() {

	std::list<Physic2D*> remove;

	for (auto object : objects) {
		if (!object->GetSprite()->clipped && !object->deleteObject) {
			if(object->wait <= 0) object->Update();
			else object->wait -= time.getElapsedMs();
		}
		else if(object->deleteObject || abs(object->GetPos().y - this->pos.y)>100 || abs(object->GetPos().x - this->pos.x) > 250) remove.push_front(object);
	}
	while (remove.size() > 0) {
		objects.remove(remove.front());
		chunks.remove((Map*)remove.front());
		collidables.remove((Collidable*)remove.front());
		delete remove.front();
		remove.pop_front();
	}
	if (georgette.wait <= 0) georgette.Update();
	else georgette.wait -= time.getElapsedMs();
	MapGenerator::Update();
}

void Game::Draw() {
	
	for (auto chunk : chunks) chunk->Draw();
	for (auto collidable : collidables) collidable->Draw();
	georgette.Draw();

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	// Draw buffer
	if(time.getElapsedMs() > 0){
		std::ostringstream strs;
		strs << (int)floor(1000 / time.getElapsedMs());
		std::string str = strs.str();
		int i = -1;
		for (char c : str) {
			buffer[0][++i].Char.UnicodeChar = c;
		}
	}
	for (int bar = 0; bar < SCREEN_WIDTH - 4; ++bar) {
		if(score/(float)MAXSCORE > bar/ (float)(SCREEN_WIDTH - 4)){
			buffer[SCREEN_HEIGHT-2][bar + 2].Char.UnicodeChar = ' ';
			buffer[SCREEN_HEIGHT - 2][bar + 2].Attributes = 0x844f;
		}
		else {
			buffer[SCREEN_HEIGHT - 2][bar + 2].Attributes = buffer[SCREEN_HEIGHT - 2][bar + 2].Attributes | 0x8400;

		}

		if(bar == 0) buffer[SCREEN_HEIGHT - 2][bar + 2].Attributes = 0x0800 | buffer[SCREEN_HEIGHT - 2][bar + 2].Attributes;
		else if (bar + 1 == SCREEN_WIDTH - 4)buffer[SCREEN_HEIGHT - 2][bar + 2].Attributes = 0x1000 | buffer[SCREEN_HEIGHT - 2][bar + 2].Attributes;
	}

	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	// Clear buffer
	bool test = false;
	for (size_t X = 0; X < SCREEN_WIDTH; ++X) {
		for (size_t Y = 0; Y < SCREEN_HEIGHT; ++Y){
			buffer[Y][X] = background.GetCase(X,Y);

		}
	}
}
void Game::ShowText(int y, std::string text, int color) {
	for (int x = 0; x < text.size(); ++x) {
		buffer[y][x + SCREEN_WIDTH / 2 - text.size() / 2].Char.UnicodeChar = text[x];
		buffer[y][x + SCREEN_WIDTH / 2 - text.size() / 2].Attributes = color;
	}
}

void Game::DrawMenu() {

	ShowText(15,"Press [Enter] to begin",0x00f0);
	ShowText(17, "CONTROL IN GAME", 0x00f4);
	ShowText(18, "Move with [Q & D]", 0x00f0);
	ShowText(19, "Jump with [Space or Z]", 0x00f0);
	ShowText(20, "Ass Shot in air with [S]", 0x00f0);
	ShowText(21, "Exit game with [Escape]", 0x00f0);

	

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	// Clear buffer
	bool test = false;
	for (size_t X = 0; X < SCREEN_WIDTH; ++X) {
		for (size_t Y = 0; Y < SCREEN_HEIGHT; ++Y) {
			buffer[Y][X] = title.GetCase(X, Y);

		}
	}
}

std::list<Map*> Game::GetChunks() {
	return Get()->chunks;
}
std::list<Collidable*> Game::GetCollidables() {
	return Get()->collidables;
}
std::list<Physic2D*> Game::GetObjects() {
	return Get()->objects;
}
void Game::AddObject(Physic2D * p) {
	this->objects.push_back(p);
}
void Game::AddChunk(Map * m) {
	this->chunks.push_back(m);
}
void Game::AddCollidable(Collidable * c) {
	this->collidables.push_back(c);
}
void Game::RemoveObject(Physic2D * p) {
	this->objects.remove(p);
}
void Game::RemoveChunk(Map * m) {
	this->chunks.remove(m);
}
void Game::RemoveCollidable(Collidable * c) {
	this->collidables.remove(c);
}

float Game::DistanceToCam(Vector2f pos) {
	return sqrt(pow(pos.x - this->pos.x, 2) + pow(pos.y - this->pos.y, 2));
}

void Game::Wait(float wait) {
	this->wait = wait;
}
void Game::ScreenShake(float time, int force) {
	screenshake = time;
	posChange.x = (rand() % 10 > 5) ? -force : force;
	posChange.y = (rand() % 10 > 5) ? -force : force;
}