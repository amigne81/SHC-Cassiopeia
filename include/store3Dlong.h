
#ifndef store3Dlong_h
#define store3Dlong_h
#include "Arduino.h"

class store3Dlong{
	private:
	const int l = 5;
	long  x,y,z;
	public:
	long dx=0 ,dy=0, dz=0; // change in direction variables
	// sets value for private values and updates their respective deltas
	void setX(long);
	void setY(long);
	void setZ(long);
	// returns private values
	long getX();
	long getY();
	long getZ();
	// outputs values in csv format
	void outCSV();
};
#endif