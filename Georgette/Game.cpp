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
void Game::SetPos(int x, int y) {
	pos.x = x;
	pos.y = y;
}

Game * Game::Get() {
	static Game game;
	return &game;
}

Game::Game() : hOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE)), i(0), pos(0,0), georgette(0,0)
{
	time.getElapsedMs(true);
}

void Game::Run() {
	Map *map = MapGenerator::GenerateFirstChunk();
	


	while (1) {
		

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
		if (!object->GetSprite()->clipped) {
			if(object->wait <= 0) object->Update();
			else object->wait -= time.getElapsedMs();


		}
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
	std::ostringstream strs;
	strs << (int)floor(1000 / time.getElapsedMs());
	std::string str = strs.str();
	int i = -1;
	for (char c : str) {
		buffer[0][++i].Char.UnicodeChar = c;
	}
	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	// Clear buffer
	bool test = false;
	for (size_t X = 0; X < SCREEN_WIDTH; ++X) {
		for (size_t Y = 0; Y < SCREEN_HEIGHT; ++Y){
			buffer[Y][X].Char.AsciiChar = ' ';
			buffer[Y][X].Attributes = 0x00f0;
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