#include "Target.h"

/*
For now at least:
values for distances are in feet
values for time are in seconds


the world will be centered around the point (0,0)

*/

Target::Target() : totalTimeElapsed(0) {
	currentPos = position(0);
	initialPos = currentPos;
};


Vector2D Target::position() {
	return currentPos;
}

Vector2D Target::position(double time) {
	// Currently a target that just moves in a straight line

	// Expand on this with different types of 2d targets?
	// make into a small demo game?

	// Make this position function driven by the initial position, not the other way around as is it now
	return Vector2D(62 * time, 40 * time) + Vector2D(0, 100);
}

void Target::update(double dtime) {
	currentPos = position(totalTimeElapsed);
	totalTimeElapsed += dtime;
}


std::vector<Vector2D> Target::flightpath(double start, double end, double step) {
	std::vector<Vector2D> path;
	double time = start;
	do {
		path.push_back(position(time));
		time += step;
	} while (time <= end);

	return path;
}