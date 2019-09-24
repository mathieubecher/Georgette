#include "pch.h"
#include "Map.h"
#include "Game.h"
Map::Map(std::string file, int x, int y, int width, int height) : Physic2D(file,x,y,width,height)
{
	Game *g = Game::Get();
	g->AddChunk(this);
}
