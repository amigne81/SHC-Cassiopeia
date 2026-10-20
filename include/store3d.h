
#ifndef store3D_h
#define store3D_h
#include "Arduino.h"

class store3D{
	private:
	int  x,y,z;
	public:
	int dx=0 ,dy=0, dz=0; // change in direction variables
	// sets value for private values and updates their respective deltas
	void setX(int);
	void setY(int);
	void setZ(int);
	// returns private values
	int getX();
	int getY();
	int getZ();
	// outputs values in csv format
	String outCSV();
};
#endif