#include "Target.h"

/*
For now at least:
values for distances are in feet
values for time are in seconds


the world will be centered around the point (0,0)

*/

Target::Target() : totalTimeElapsed(0) {
	currentPos = Vector2D(0, 0);
	initialPos = Vector2D(0, 0);

};

Target::Target(double xStart, double yStart) : totalTimeElapsed(0) {
	initialPos = Vector2D(xStart, yStart);
	currentPos = initialPos;
	m_isBroken = false;
};


Vector2D Target::currentPosition() const {
	return currentPos;
}


void Target::update(double dtime) {
	currentPos = position(totalTimeElapsed);
	totalTimeElapsed += dtime;
}

bool Target::isBroken() {
	return m_isBroken;
}

void Target::breakTarget() {
	m_isBroken = true;
}


std::vector<Vector2D> Target::flightpath(double start, double end, double step) const{
	std::vector<Vector2D> path;
	double time = start;
	do {
		path.push_back(position(time));
		time += step;
	} while (time <= end);

	return path;
}