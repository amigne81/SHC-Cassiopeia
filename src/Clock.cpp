

#include "Clock.h"



unsigned long int Clock::t(){
	return millis();
}

void Clock::setdt(){
	Clock::dt = millis() - previous; 
	previous = millis();
}	
