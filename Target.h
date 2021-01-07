#pragma once
#include "Vector2D.h"
#include <vector>
class Target
{
private:
	Vector2D pos;
	double totalTimeElapsed;

public:

	Target();
	Target(double x, double y);

	Vector2D velocity(double time);
	const Vector2D& position();
	void update(double dtime);

};

std::vector<Vector2D> flightpath(Target t, double start, double end, double step);

