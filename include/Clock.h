
#ifndef Clock_h
#define Clock_h

#include "Arduino.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

class Clock {
	private: 
	unsigned long int previous = 0;
	const int l = 5;
 

	public:	
	unsigned long int dt;
	unsigned long int t();
	void setdt();

};

#endif
