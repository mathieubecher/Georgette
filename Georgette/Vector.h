#pragma once

struct Vector2
{
public:
	int x;
	int y;

	Vector2(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Vector2() {
		this->x = 0;
		this->y = 0;
	}
};

struct Vector2f
{
public:
	float x;
	float y;

	Vector2f(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Vector2f() {
		this->x = 0;
		this->y = 0;
	}
};