
#ifndef Clock_h
#define Clock_h

#include "Arduino.h"

class Clock {
	
	public:
	
	unsigned long int elapsedTime;
	
	Clock(int);
	
	void set();
	bool check();
	bool checkMan(int);
	int checkAndWait();
	
	private:
		
	int ticSpeed; //used for the constructor
<<<<<<< HEAD
	unsigned int exceededTime;
	unsigned long int currTime;
=======

	unsigned long exceededTime;
		
	unsigned long currTime;
>>>>>>> e745c8aeca7ac83e99be1fba1f54c75a560e5f43
};

#endif
