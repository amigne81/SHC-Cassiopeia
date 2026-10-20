

#include "Clock.h"

void Clock::setUTC(String a){
	utc = a;
}

unsigned long int Clock::t(){
	return millis();
}

String Clock::UTC(){
	return "";
}

void Clock::setdt(){
	Clock::dt = millis() - previous; 
	previous = millis();
}	
