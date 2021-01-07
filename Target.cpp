#include "Target.h"

Target::Target() : totalTimeElapsed(0) {
	Vector2D v(0, 0);
	pos = v;
};

Target::Target(double x, double y) : totalTimeElapsed(0) {
	Vector2D v(x, y);
	pos = v;
};

// The velocity of the target at time time
Vector2D Target::velocity(double time) {
	// can return based on more complex functions
	Vector2D v(75, -cos(time) * 150);
	return v;
}

const Vector2D& Target::position() {
	return pos;
}

void Target::update(double dtime) {
	Vector2D vel = velocity(totalTimeElapsed) * dtime;
	pos = pos + vel;
	totalTimeElapsed += dtime;
}


std::vector<Vector2D> flightpath(Target t, double start, double end, double step) {
	std::vector<Vector2D> path;
	double time = start;
	do {
		path.push_back(t.position());
		t.update(step);
		time += step;
	} while (time <= end);

	return path;
}