#pragma once
#include "Vector2D.h"
class Shooter
{
private:
	Vector2D position;
	double shotSpeed;

public:
	Shooter(double x, double y, double shotSpeed) : position(Vector2D(x, y)), shotSpeed(shotSpeed) {};
	Vector2D getPosition() const { return position; };
	double getShotSpeed() const { return shotSpeed; };
};

