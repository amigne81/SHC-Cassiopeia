
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

	String outCSV();
};

#endif
