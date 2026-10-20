
#ifndef Data_h
#define Data_h

#include "store3Dlong.h"
#include "store3Ddouble.h"
#include "Clock.h"
#include "Arduino.h"

struct Data{
	public:
	store3Ddouble Acc, Gyro;
	store3Dlong GPS;
	Clock time;
	int tempI, tempE, pressure, humidity;
	int state;
	int ID = 1234;
	int count = 0;

	int getTempI();
	int getTempE();
	double getAccX();
	double getAccY();
	double getAccZ();
	double getGyroX();
	double getGyroY();
	double getGyroZ();
	long getH();
	long getDh();

	String outCSV();
};

#endif
