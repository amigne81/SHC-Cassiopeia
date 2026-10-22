
#ifndef Data_h
#define Data_h

#include "store3Dlong.h"
#include "store3Ddouble.h"
#include "Clock.h"
#include "Arduino.h"

struct Data{
	public:
	store3Ddouble Acc, Gyro;
	store3Ddouble GPS;
	Clock time;
	int tempI, tempE, pressure, humidity;
	int state;
	String UTC;

	Data();

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

	private:
	const int l = 5;
	String ID = "Cassiopia";
	int count = 0;
};

#endif
