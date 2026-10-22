
#ifndef Clock_h
#define Clock_h

#include "Arduino.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

class Clock {
	private: 
	unsigned long int previous = 0;
	String utc;
	const int l = 5;
 

	public:
	void setUTC(SFE_UBLOX_GNSS*);	
	unsigned long int dt;
	unsigned long int t();
	String UTC();
	void setdt();

};

#endif
