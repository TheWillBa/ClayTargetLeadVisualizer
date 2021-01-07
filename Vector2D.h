#pragma once
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
	
};

