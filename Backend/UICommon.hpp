#pragma once
#include "Common.hpp"

typedef struct {
	int X;
	int Y;
} UICoord;

typedef struct {
	float X;
	float Y;
} UICoordF;

#define COLLIDE(mx, my, x, y, w, h) ((mx >= x && mx <= (x + w)) && (my >= y && my <= (y + h)))