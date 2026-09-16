
#include "Arduino.h"
#include "Clock.h"

/**
*Constructor for Clock. Takes tic speed.
**/
Clock::Clock(int ticSpeed) {
	this->ticSpeed = ticSpeed; //NOT this.ticSpeed
}

//**********METHODS***********

/**
*Stores the current time
**/
void Clock::set() {
	currTime = millis();
}

/**
*True: Time elapsed is less than or equal to the tic speed
*False: Time elapsed has exceeded the tic requirement
**/
bool Clock::check() {
	unsigned long elapsedTime = millis()-currTime;
	
	return !( elapsedTime > ticSpeed );//elapsedTime <= ticSpeed
}

/**
*True: Time elapsed is less than or equal to the input time
*False: Time elapsed has exceeded the inputted time
**/
bool Clock::checkMan(int time) {
	unsigned long elapsedTime = millis()-currTime;
	
	return ! ( elapsedTime > time );//elapsedTime <= time
}

/**
*Checks the current time and if it is within the tic parameter. 
*It will delay until the end of the tic.
*
*return:
*  the exceeded time, if time elapsed is less than or equal to the tic speed
*  zero, if the time elapsed has exceeded the inputted time
**/
int Clock::checkAndWait() {
	unsigned long elapsedTime = millis()-currTime;
	
	if (check()) {
		exceededTime = ticSpeed-elapsedTime;
		
		delay(exceededTime);
		return exceededTime;
	}
	return 0;
}