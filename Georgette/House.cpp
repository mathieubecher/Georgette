#include "pch.h"
#include "House.h"
#include "Game.h"
#include "People.h"
House::House(CHAR_INFO *sprite, int x, int y, int width, int height) : Map(sprite,x,y,width,height) {

}

bool House::IsHouse() {
	return true;
}

House::~House()
{
}
void House::Update() {
	for(auto caseSave : casesSave){
		if (sprite.GetCase(caseSave.x, caseSave.y).Char.UnicodeChar == ' ') AddPeople(caseSave.x+pos.x, caseSave.y + pos.y);
	}

	Map::Update();

}
void House::AddPeople(int x, int y) {
	if(rand()%2 == 0) People * p = new People(x, y);
}
