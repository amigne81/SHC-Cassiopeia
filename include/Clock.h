
#ifndef Clock_h
#define Clock_h

#include "Arduino.h"

class Clock {
	private: 
	unsigned long int previous = 0;
	String utc;
	
	public:
	unsigned long int dt;
	void setUTC(); 
	unsigned long int t();
	void setdt();

};

#endif
