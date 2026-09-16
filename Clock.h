
#ifndef Clock_h
#define Clock_h

#include "Arduino.h";

class Clock {
	
	public:
	
	unsigned long elapsedTime;
	
	Clock(int);
	
	void set();
	bool check();
	bool checkMan(int);
	int checkAndWait();
	
	private:
		
	int ticSpeed; //used for the constructor
		
	unsigned long currTime;
};

#endif
