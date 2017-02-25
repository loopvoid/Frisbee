#ifndef FRISBEE_H
#define FRISBEE_H

#define PI 3.1415926

class Frisbee
{
public:
	static void simulate(double y0, double vx0, double vy0, double alpha, double deltaT);
private:
	static double x;
	static double y;
	static double vx;
	static double vy;
	static const double g;		//
	static const double m;		//
	static const double RHO;	//
	static const double AREA;	//
	static const double CL0;	//
	static const double CLA;	//
	static const double CD0;	//
	static const double CDA;	//
	static const double ALPHA0;	//
};

#endif