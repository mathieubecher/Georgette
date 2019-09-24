#include "pch.h"
#include "MapGenerator.h"
#include "Game.h"

Vector2 const MapGenerator::SIZE(80,40);

MapGenerator::MapGenerator()
{
}


MapGenerator::~MapGenerator()
{
}

Map *MapGenerator::GenerateChunk(Vector2 pos) {

	return nullptr;
}


Map *MapGenerator::FindChunk(Vector2 pos) {
	Game::GetChunks();



	return nullptr;
}