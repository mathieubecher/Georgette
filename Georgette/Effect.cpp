#include "pch.h"
#include "Effect.h"
#include "Game.h"

Effect::Effect()
{
	Game::Get()->AddEffect(this);
}


Effect::~Effect()
{
	//Game::Get()->RemoveEffect(this);
}

void Effect::Update() {

}