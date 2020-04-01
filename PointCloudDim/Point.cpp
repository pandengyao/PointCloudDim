#include "Point.h"

Point Point::operator=(const Point &rhs)
{
	if (this == &rhs) return *this; // handle self assignment
	//assignment operator
	X = rhs.X;
	Y = rhs.Y;
	Z = rhs.Z;
	return *this;
}

Point Point::operator+(const Point &rhs)
{
	return (Point(X + rhs.X, Y + rhs.Y, Z + rhs.Z));
}

Point Point::operator-(const Point &rhs)
{
	return (Point(X - rhs.X, Y - rhs.Y, Z - rhs.Z));
}

std::ostream &operator<<(std::ostream &output, const Point &rhs)
{
	output << "(" << rhs.X << "," << rhs.Y << "," << rhs.Z << ")";
	return output;
}

Point Point::operator*(Point &pt)
{
	double x1, x2, y1, y2, z1, z2, vx, vy, vz;
	x1 = GetX();
	x2 = pt.GetX();
	y1 = GetY();
	y2 = pt.GetY();
	z1 = GetZ();
	z2 = pt.GetZ();

	vx = y1 * z2 - y2 * z1;
	vy = -x1 * z2 + x2 * z1;
	vz = x1 * y2 - x2 * y1;

	return Point(vx, vy, vz);
}
