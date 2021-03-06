#pragma once
#include <SDL.h>
#include <vector>
#include "Constants.h"
#include "Player.h"
#include "Box.h"
#include "Enemy.h"

bool CheckCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{

	if (x1 < x2 + w2 && x1 + w1 > x1 && y1 < y2 + h2 && h1 + y1 > y2){
		return true;
	}
	return false;
}