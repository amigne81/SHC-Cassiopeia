
#ifndef Data_h
#define Data_h

#include "store3D.h"
#include "Clock.h"
#include "string"

struct Data{
	public:
	store3D Acc, Gyro, GPS;
	Clock time;
	int temp;
	int state;
	int ID = 123456789;
	int count = 0;

	int getTemp();
	int getAccX();
	int getAccY();
	int getAccZ();
	int getGyroX();
	int getGyroY();
	int getGyroZ();
	int getH();
	int getDh();

	std::string outCSV(int);
};

#endif
