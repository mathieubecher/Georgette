#pragma once
#include "Effect.h"
#include "Vector.h"
class ScreenShake: public Effect
{
private:
	float time;
	float force;
	Vector2 pos;
public:
	ScreenShake();
	ScreenShake(float time, float force);
	void Update();
};

