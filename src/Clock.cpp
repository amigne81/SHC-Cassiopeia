

#include "Clock.h"



unsigned long int Clock::t(){
	return millis();
}

String Clock::UTC(){
	return utc;
}

void Clock::setdt(){
	Clock::dt = millis() - previous; 
	previous = millis();
}	
