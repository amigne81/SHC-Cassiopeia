
#ifndef store3D_h
#define store3D_h
#include "Arduino.h"

class store3D{
	private:
	double  x,y,z;
	public:
	double dx=0 ,dy=0, dz=0; // change in direction variables
	// sets value for private values and updates their respective deltas
	void setX(double);
	void setY(double);
	void setZ(double);
	// returns private values
	double getX();
	double getY();
	double getZ();
	// outputs values in csv format
	String outCSV();
};
#endif