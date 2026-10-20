
#ifndef Clock_h
#define Clock_h

#include "Arduino.h"

class Clock {
	private: 
	unsigned long int previous = 0;
	unsigned long int utc;

	public:
	void setUTC(unsigned long int); 
	unsigned long int t();
	unsigned long int tUTC();
	unsigned long int dt();
	
	/*
	public:
	
	unsigned long int elapsedTime;
	
	Clock(int);
	
	void set();
	bool check();
	bool checkMan(int);
	int checkAndWait();
	
	private:
		
	int ticSpeed; //used for the constructor

	unsigned long exceededTime;
		
	unsigned long currTime;
	*/
};

#endif
