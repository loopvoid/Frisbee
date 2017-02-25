#include"Frisbee.h"
#include<math.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const double Frisbee::g = -9.81;
const double Frisbee::m = 0.175;
const double Frisbee::RHO = 1.23;
const double Frisbee::AREA = 0.0568;
const double Frisbee::CL0 = 0.1;
const double Frisbee::CLA = 1.4;
const double Frisbee::CD0 = 0.08;
const double Frisbee::CDA = 2.72;
const double Frisbee::ALPHA0 = -4;
double Frisbee::vx = 0;
double Frisbee::vy = 0;
double Frisbee::x = 0;
double Frisbee::y = 0;

void Frisbee::simulate(double y0, double vx0, double vy0, double alpha, double deltaT)
{
	//Calculation of the lift coefficient using the relationship given
	//by S. A. Hummel.
	double cl = CL0 + CLA*alpha*PI / 180;
	//Calculation of the drag coefficient (for Prantl’s relationship)
	//using the relationship given by S. A. Hummel.
	double cd = CD0 + CDA*pow((alpha - ALPHA0)*PI / 180, 2);
	//Initial position x = 0.
	x = 0;
	//Initial position y = y0.
	y = y0;
	//Initial x velocity vx = vx0.
	vx = vx0;
	//Initial y velocity vy = vy0.
	vy = vy0;
	try{
		//A PrintWriter object to write the output to a spreadsheet.
		//PrintWriter pw = new PrintWriter(new BufferedWriter
		//	(new FileWriter("frisbee.csv")));

		ofstream fout;
		fout.open("frisbee.csv", ios_base::app);
		if (!fout.is_open())
		{
			throw "文件打开失败!";
		}

		//A loop index to monitor the simulation steps.
		int k = 0;
		//A while loop that performs iterations until the y position
		//reaches zero (i.e. the frisbee hits the ground).
		while (y > 0){
			//The change in velocity in the y direction obtained setting the
			//net force equal to the sum of the gravitational force and the
			//lift force and solving for delta v.
			double deltavy = (RHO*pow(vx, 2)*AREA*cl / 2 / m + g)*deltaT;
			//The change in velocity in the x direction, obtained by
			//solving the force equation for delta v. (The only force
			//present is the drag force).
			double deltavx = -RHO*pow(vx, 2)*AREA*cd*deltaT;
			//The new positions and velocities are calculated using
			//simple introductory mechanics.
			vx = vx + deltavx;
			vy = vy + deltavy;
			x = x + vx*deltaT;
			y = y + vy*deltaT;
			//Only the output from every tenth iteration will be sent
			//to the spreadsheet so as to decrease the number of data points.
			if (k % 10 == 0){
				//pw.print(x + "," + y + "," + vx);
				fout << x << "," << y << "," << vx;
				//pw.println();
				//fout << "\r\n";
				fout << "\n";
				fout.flush();
			}
			k++;
		}
		fout.close();
	}
	catch (string s){
		cout << s + "Error, file frisbee.csv is in use.";
	}
}

int main()
{
	Frisbee::simulate(1, 16.5, 0, 6, 0.001);

	return 0;
}