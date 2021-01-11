#pragma once
#include "Vector2D.h"
class Shooter
{
private:
	Vector2D position;

	// Remove shotspeed from shooter?
	double shotSpeed;

	float speed;
	float rotation;
	float rotationSpeed;
	float shotPatternSize;

public:
	Shooter(double x, double y, double shotSpeed) : position(Vector2D(x, y)), shotSpeed(shotSpeed) {
		speed = 15.0f;
		rotation = 3.141592 / 2;
		rotationSpeed = 4.0f;
		shotPatternSize = 3;
	};
	Vector2D getPosition() const { return position; };
	double getShotSpeed() const { return shotSpeed; };
	float getShotPatternSize() const { return shotPatternSize; };

	void moveForwards(double dtime) { position = position + currentlyFacing() * speed * dtime; };
	void moveBackwards(double dtime) { position = position + currentlyFacing() * -speed * dtime; };
	void strafeRight(double dtime) { position = position + currentlyFacing().perp() * speed * dtime; }
	void strafeLeft(double dtime) { position = position + currentlyFacing().perp() * -speed * dtime; }
	
	Vector2D currentlyFacing() { return  Vector2D(cos(rotation), sin(rotation)); }
	void rotateClockwise(double dtime) { rotation -= rotationSpeed * dtime; };
	void rotateCounterClockwise(double dtime) { rotation += rotationSpeed * dtime; }
};

