#include "Vector2D.h"
Vector2D::Vector2D() : x(0), y(0) {};
Vector2D::Vector2D(double x, double y) : x(x), y(y) {};

double Vector2D::X() const { return x; };
double Vector2D::Y() const { return y; };

Vector2D Vector2D::operator+ (const Vector2D& other) const {
	Vector2D v(x + other.x, y + other.y);
	return v;
}

bool Vector2D::operator== (const Vector2D& other) const {
	return (x == other.x) && (y == other.y);
}

Vector2D Vector2D::operator* (double scalar) const {
	Vector2D v(x * scalar, y * scalar);
	return v;
}

Vector2D Vector2D::operator* (int scalar) const {
	Vector2D v(x * scalar, y * scalar);
	return v;
}