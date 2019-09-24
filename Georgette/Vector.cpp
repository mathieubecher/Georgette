#include "Vector.h"
#include <math.h>

bool Vector2::operator==(const Vector2f& other) const {
	return this->x == (int)floor(other.x) && this->y == (int)floor(other.y);
}


bool Vector2::operator==(const Vector2& other) const {
	return this->x == other.x && this->y == other.y;
}


bool Vector2f::operator==(const Vector2& other) const {
	return (int)floor(this->x) == other.x && (int)floor(this->y) == other.y;
}