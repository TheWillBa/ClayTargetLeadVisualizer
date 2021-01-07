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
	double angle;
	double xVelocity;
	double yVelocity;

public:
	LinearTarget(double x, double y, double velocity, double angle) : Target{ x,y }, angle(-angle * (3.141592) / 180){
		xVelocity = velocity * cos(this->angle);
		yVelocity = velocity * sin(this->angle);

	};

	Vector2D position(double time) override {
		// make into a small demo game?
		return Vector2D(xVelocity * time, yVelocity * time) + initialPos;
	};
	

};

