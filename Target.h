#pragma once
#include "Vector2D.h"
#include <vector>
class Target
{
private:
	Vector2D currentPos;
	double totalTimeElapsed;

protected:
	Vector2D initialPos;

public:

	Target();
	Target(double xStart, double yStart);

	virtual Vector2D position(double time) = 0;
	virtual Vector2D position();
	void update(double dtime);

	std::vector<Vector2D> flightpath(double start, double end, double step);
};



