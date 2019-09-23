#include "pch.h"
#include "Game.h"

CHAR_INFO * Game::Buffer() {
	return *this->buffer;
}

Game * Game::Get() {
	if (!Game::game)
		Game::game = new Game();
	return Game::game;
}

Game::Game() : objet(1,1), hOutput((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE)), i(0)
{
	time.getElapsedMs(true);
	Game::game = this;
	while(1){
		//std::cerr << timeDraw;
		if (time.getElapsedMs() > 1000.0f / MAXFRAME) {
			time.getElapsedMs(true);
			Update();
			Draw();
		}
	}

}

void Game::Update() {
	

	++i;
	if (i + 2 >= SCREEN_HEIGHT * SCREEN_WIDTH) i = 0;
	
}

void Game::Draw() {
	
	int Hx = i % SCREEN_WIDTH;
	int Hy = i / SCREEN_WIDTH;
	
	int ix = (i+1) % SCREEN_WIDTH;
	int iy = (i+1) / SCREEN_WIDTH;

	int pointx = (i+2) % SCREEN_WIDTH;
	int pointy = (i+2) / SCREEN_WIDTH;

	buffer[Hy][Hx].Char.AsciiChar = 'H';
	buffer[Hy][Hx].Attributes = 0x0E;
	buffer[iy][ix].Char.AsciiChar = 'i';
	buffer[iy][ix].Attributes = 0x0B;
	buffer[pointy][pointx].Char.AsciiChar = '!';
	buffer[pointy][pointx].Attributes = 0x0A;

	this->objet.Draw();

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	// Clear Screen
	system("CLS");
	// Draw buffer
	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
	// Clear buffer
	
	for (size_t X = 0; X < SCREEN_WIDTH; ++X) {
		for (size_t Y = 0; Y < SCREEN_HEIGHT; ++Y)
			buffer[Y][X].Char.AsciiChar = ' ';
	}
	
}

Game::~Game()
{
}

Game * Game::game = nullptr;
