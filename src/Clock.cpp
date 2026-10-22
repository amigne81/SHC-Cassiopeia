

#include "Clock.h"

void Clock::setUTC(SFE_UBLOX_GNSS* p){
	utc = String(p->getHour(),l)	+", ";//+ 
	String(p->getMinute(),l) 		+", "+
	String(p->getSecond(),l) 		+", "+
	String(p->getTimeOfWeek()) 		+", "+
	String(p->getMonth()) 			+", "+
	String(p->getDay(),l)			+", "+
	String(p->getYear(),l)			+", ";
}

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
