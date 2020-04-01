#ifndef POINT_H
#define POINT_H
#include<iostream>
#include<cmath>

class Point
{
public:
	Point(double _x = 0.0, double _y = 0.0, double _z = 0.0) :X(_x), Y(_y), Z(_z) {};
	virtual ~Point() {};
	Point(const Point &other) { X = other.X; Y = other.Y; Z = other.Z; };
	Point operator=(const Point&);
	Point operator+(const Point&);
	Point operator-(const Point&);
	Point operator*(Point&);
	friend std::ostream &operator<<(std::ostream &output, const Point &rhs);

	double GetX() { return X; }
	void SetX(double val) { X = val; }
	double GetY() { return Y; }
	void SetY(double val) { Y = val; }
	double GetZ() { return Z; }
	void SetZ(double val) { Z = val; }
	double dotX(Point &pt) { return (pt.GetX()*GetX() + pt.GetY()*GetY() + pt.GetZ()*GetZ()); }
	double mod() { return sqrt(dotX(*this)); }

protected:

private:
	double X;
	double Y;
	double Z;
};

#endif // POINT_H