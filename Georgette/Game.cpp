#include "pch.h"
#include "Game.h"
#include "Hi.h"
#include "Map.h"
#include "Rigidbody.h"
#include "Collidable.h"
#include "Devil.h"

CHAR_INFO * Game::Buffer() {
	return *this->buffer;
}
Vector2 Game::Pos() {
	return this->pos;
} 
void Game::SetPos(int x, int y) {
	pos.x = x;
	pos.y = y;
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
	Devil georgette = Devil(6,5);
	Collidable test = Collidable();


	while (1) {
		if (time.getElapsedMs() > 1000.0f / MAXFRAME) {
			Update();
			Draw();
			time.getElapsedMs(true);
		}
	}
}

void Game::Update() {

	for (auto object : objects) object->Update();
}

void Game::Draw() {

	for (auto chunk : chunks) chunk->Draw();
	for (auto collidable : collidables) collidable->Draw();


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

std::list<Map*> *Game::GetChunks() {
	return &Get()->chunks;
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
Game::~Game()
{
}

Game * Game::game = nullptr;
