

#include "Clock.h"

Clock::Clock(){
}

Clock::Clock(SFE_UBLOX_GNSS* a){
	p = a;
}

void Clock::setUTC(){
	utc = String(p->getHour(),l)	+", ";//+ 
	//String(p->getMinute(),l) 		+", "+
	//String(p->getSecond(),l) 		+", "+
	//String(p->getTimeOfWeek()) 		+", "+
	//String(p->getMonth()) 			+", "+
	//String(p->getDay(),l)			+", "+
	//String(p->getYear(),l)			+", ";
}

unsigned long int Clock::t(){
	return millis();
}

String Clock::UTC(){
	setUTC();
	return utc;
}

void Clock::setdt(){
	Clock::dt = millis() - previous; 
	previous = millis();
}	
