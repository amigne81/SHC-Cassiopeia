
#include "Arduino.h"
#include "Clock.h"

void Clock::setUTC(unsigned long int a){
	Clock::utc = a;
}

unsigned long int Clock::t(){
	return millis();
}

unsigned long int Clock::tUTC(){
	return millis() + Clock::utc;
}

void Clock::setdt(){
	Clock::dt = millis() - previous; 
	previous = millis();
}	
