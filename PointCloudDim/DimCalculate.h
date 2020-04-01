#pragma once
#include "Point.h"
#include "PlaneEquation.h"

class DimCalculate
{
public:
	DimCalculate();
	~DimCalculate();

	double dist(Point &pt1, Point &pt2);  //Distance between two points
	double dist(Point &ptA, Point &ptB, Point &ptC); //ptA(x0,y0,z0) ptB(x1,y1,z1) ptC为方向向量(l,m,n)
	double dist(Point &pt, PlaneEquation &pe); //Distance between point and plane
};

