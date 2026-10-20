
#ifndef Clock_h
#define Clock_h

#include "Arduino.h"

class Clock {
	private: 
	unsigned long int previous = 0;
	unsigned long int utc;
	
	public:
	unsigned long int dt;
	void setUTC(unsigned long int); 
	unsigned long int t();
	unsigned long int tUTC();
	void setdt();

};

#endif
