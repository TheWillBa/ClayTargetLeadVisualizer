#include "Vector2D.h"
#include <math.h>
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

double Vector2D::operator* (const Vector2D& other) const {
	return x * other.x + y * other.y;
}

double Vector2D::distance(const Vector2D& other) const {
	return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

double Vector2D::cosAngleBetween(const Vector2D& other) const {
	return (*this * other) / (this->magnitude() * other.magnitude());
}

double Vector2D::magnitude() const{
	return sqrt((x * x) + (y * y));
}

Vector2D Vector2D::operator- (const Vector2D& other) const {
	return Vector2D(x - other.x, y - other.y);
}

double Vector2D::polarAngle() const {
	double a = fmod(atan2(y, x) , (2 * 3.141592));
	if (a >= 0) return a;
	return 2 * 3.141592 + a;
}