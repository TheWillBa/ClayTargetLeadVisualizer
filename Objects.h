#pragma once
#include "olcPixelGameEngine.h"
#include "Vector2D.h"

struct RectGroundObject {
	int height;
	int wigth;
	olc::Pixel color;
	Vector2D position;

	RectGroundObject(int w, int h, const Vector2D& position, const olc::Pixel& color) :
		wigth(w), height(h), position(position), color(color) {};
};