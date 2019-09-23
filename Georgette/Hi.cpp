#include "pch.h"
#include "Hi.h"
#include "Game.h"


void Hi::Update() {
	++pos.x;
	if (pos.x > SCREEN_WIDTH) {
		pos.x = 0;
		++pos.y;
		if (pos.y > SCREEN_HEIGHT) pos.y = 0;
	}
	Physic2D::Update();
}