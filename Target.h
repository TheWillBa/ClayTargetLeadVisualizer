#pragma once
#include "Vector2D.h"
#include <vector>
class Target
{
private:
	Vector2D initialPos;
	Vector2D currentPos;
	double totalTimeElapsed;

public:

	Target();

	Vector2D position(double time);
	Vector2D position();
	void update(double dtime);

	std::vector<Vector2D> flightpath(double start, double end, double step);
};



