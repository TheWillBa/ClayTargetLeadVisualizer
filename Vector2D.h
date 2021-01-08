#pragma once
#include <string>

class Vector2D
{
private:
	double x;
	double y;

public:
	Vector2D();
	Vector2D(double x, double y);
	double X() const;
	double Y() const;

	Vector2D operator+ (const Vector2D& other) const;
	Vector2D operator- (const Vector2D& other) const;
	bool operator== (const Vector2D& other) const;
	Vector2D operator* (double scalar) const;
	Vector2D operator* (int scalar) const;
	// Dot product
	double operator* (const Vector2D& other) const;
	double distance(const Vector2D& other) const;
	double cosAngleBetween(const Vector2D& other) const;
	double magnitude() const;
	double polarAngle() const;
	Vector2D rotated90CCW() const;

	/*
	Returns -1 if this vector is to the left of other, 1 if to the right
	*/
	int onSide(const Vector2D& other) const;
	Vector2D perp() const;
	std::string toString() {
		return "X: " + std::to_string(x) + ", Y: " + std::to_string(y);
	}
	
};

