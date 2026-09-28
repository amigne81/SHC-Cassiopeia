
#ifndef Data_h
#define Data_h

#include "store3D.h"
#include "Clock.h"

struct Data{
	public:
	store3D Acc, Gyro, GPS;
	Clock time;
	int temp;
	
	int getTemp();
	int getAccX();
	int getAccY();
	int getAccZ();
	int getGyroX();
	int getGyroY();
	int getGyroZ();
	int getH();
	int getDh();
}

#endif
