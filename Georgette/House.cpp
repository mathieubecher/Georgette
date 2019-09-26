#include "pch.h"
#include "House.h"
#include "Game.h"

House::House(CHAR_INFO *sprite, int x, int y, int width, int height) : Map(sprite,x,y,width,height) {

}

bool House::IsHouse() {
	return true;
}

House::~House()
{
}
