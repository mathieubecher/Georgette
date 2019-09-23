#pragma once
#include "Windows.h"
#include <stdio.h>
#include <iostream>
#include "NYTimer.h"

struct Vector2
{
public:
	int x;
	int y;
	Vector2(const int &x, const int &y) {
		this->x = x;
		this->y = y;
	}
	Vector2() {
		Vector2(0, 0);
	}
};	

class Physics2D
{
private:
	Vector2 size;
	CHAR_INFO * sprite;
public:
	Physics2D(std::string file);
	Physics2D(Vector2 size);
	Physics2D(int x, int y);
	~Physics2D();
};

