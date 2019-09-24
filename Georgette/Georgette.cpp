// Georgette.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "Game.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>

#include <thread>   

int main()
{
	Game *g = Game::Get();
	g->Run();
	return 0;
}

