

#include "Clock.h"

void Clock::setUTC(SFE_UBLOX_GNSS* p){
	
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
