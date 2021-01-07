#pragma once
#include "Target.h"
#include <cmath>

/*
A target that moves in a straight line at a constant velocity 
from a starting position and angle offset
*/

class LinearTarget : public Target
{
private:
	double angleR;
	double angleE;
	Vector2D velocity;
	double velocityMag;

public:
	LinearTarget(double x, double y, double velocity, double angle) : 
		Target{ x,y }, angleR(-angle * (3.141592) / 180), angleE(angle){
		this->velocity = Vector2D(velocity * cos(this->angleR), velocity * sin(this->angleR));
		velocityMag = velocity;
	};

	Vector2D position(double time) const override {
		// make into a small demo game?
		return Vector2D(velocity.X() * time, velocity.Y() * time) + initialPos;
	};


	Vector2D getVelocity() { return velocity; };
	double getVelocityMagitude() { return velocityMag; };
	double angleRadians() { return angleR; };

};

