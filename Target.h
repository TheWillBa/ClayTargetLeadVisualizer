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

	virtual Vector2D position(double time) const = 0;
	Vector2D currentPosition() const;
	void update(double dtime);
	double time() { return totalTimeElapsed; };

	std::vector<Vector2D> flightpath(double start, double end, double step) const;
};



