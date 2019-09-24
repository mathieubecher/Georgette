#include "pch.h"
#include "Game.h"
#include "Hi.h"
#include "Map.h"
#include "Rigidbody.h"

CHAR_INFO * Game::Buffer() {
	return *this->buffer;
}
Vector2 Game::Pos() {
	return this->pos;
} 

Game * Game::Get() {
	if (!Game::game)
		Game::game = new Game();
	return Game::game;
}

Game::Game() : hOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE)), i(0), pos(0,0)
{
	time.getElapsedMs(true);
	Game::game = this;
}

void Game::Run() {
	Map map = Map("tile/map.spr",0,0,0,0);
	Rigidbody georgette = Rigidbody("georgette/georgette_idle.spr",5.9f,5,5,3);
	Physic2D test = Physic2D();
	Hi hi = Hi();


	while (1) {
		if (time.getElapsedMs() > 1000.0f / MAXFRAME) {
			time.getElapsedMs(true);
			Update();
			Draw();
		}
	}
}

void Game::Update() {

	for (auto object : objects) object->Update();
}

void Game::Draw() {

	for (auto object : objects) object->Draw();

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	// Draw buffer
	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	// Clear buffer
	bool test = false;
	for (size_t X = 0; X < SCREEN_WIDTH; ++X) {
		for (size_t Y = 0; Y < SCREEN_HEIGHT; ++Y){
			buffer[Y][X].Char.AsciiChar = ' ';
			buffer[Y][X].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
			
		}
	}
}

std::list<Map*> Game::GetChunks() {
	return Get()->chunks;
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
Game::~Game()
{
}

Game * Game::game = nullptr;
