#include "pch.h"
#include "Physics2D.h"


Physics2D::Physics2D(std::string file) {

}
Physics2D::Physics2D(Vector2 size)
{
	this->size = size;
	sprite = new CHAR_INFO[this->size.x*this->size.y];
}
Physics2D::Physics2D(int x,int y)
{
	Physics2D(Vector2(x,y));
}

Physics2D::~Physics2D()
{
	delete [] sprite;
}
