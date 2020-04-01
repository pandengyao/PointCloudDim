#include "DimCalculate.h"
#include <cmath>
using namespace std;


DimCalculate::DimCalculate()
{
}


DimCalculate::~DimCalculate()
{
}


double DimCalculate::dist(Point &pt1, Point &pt2)  //Distance between two points
{
	return (pt2 - pt1).mod();
}


double DimCalculate::dist(Point &ptA, Point &ptB, Point &ptC) //ptA(x0,y0,z0) ptB(x1,y1,z1) ptC为方向向量(l,m,n)
{
	double d = 0;
	double denominator = ptC.dotX(ptC);
	if (denominator == 0) {
		cout << "分母为零" << endl;
		return 0;
	}
	else {
		double t = (ptB - ptA).dotX(ptC) / denominator;
		d = sqrt((ptA.GetX() + ptC.GetX()*t - ptB.GetX())*(ptA.GetX() + ptC.GetX()*t - ptB.GetX())
			+ (ptA.GetY() + ptC.GetY()*t - ptB.GetY())*(ptA.GetY() + ptC.GetY()*t - ptB.GetY())
			+ (ptA.GetZ() + ptC.GetZ()*t - ptB.GetZ())*(ptA.GetZ() + ptC.GetZ()*t - ptB.GetZ()));
		return d;
	}
}


double DimCalculate::dist(Point &pt, PlaneEquation &pe) //Distance between point and plane
{
	double dt = 0.0;
	double mA, mB, mC, mD, mX, mY, mZ;

	mA = pe.GetA();
	mB = pe.GetB();
	mC = pe.GetC();
	mD = pe.GetD();

	mX = pt.GetX();
	mY = pt.GetY();
	mZ = pt.GetZ();

	if (mA*mA + mB * mB + mC * mC) { dt = abs(mA*mX + mB * mY + mC * mZ + mD) / sqrt(mA*mA + mB * mB + mC * mC); }
	else { dt = pt.mod(); } // The plane is reduced to the origin. point(pt) to point(zero) distance.
	return dt;
}
