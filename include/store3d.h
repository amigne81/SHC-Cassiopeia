
#ifndef store3D_h
#define store3D_h
#include "string"

class store3D{
	private:
	int x,y,z;
	public:
	int dx=0 ,dy=0, dz=0; // change in direction variables
	// sets value for private values and updates their respective deltas
	void setX(int a);
	void setY(int a);
	void setZ(int a);
	// returns private values
	int getX();
	int getY();
	int getZ();
	// outputs values in csv format
	std::string outCSV();
	std::string outDCSV();
};
#endif