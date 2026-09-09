
/*
this library will help as an example for when you create your own libraries :) yippee!
* this is one of the two ways to write a comment in c++ everything in between the asterisks and slashes will be a comment
* this is a great way to store expirental or outdated code that you might need later!
*/

/* it works like this!*/

#ifndef LibEx_h;
#define LibEx_h;

#include "arduino.h";


// a class is like a preset that the computer can use to recreate multiple identical copied versions of your code
// using a class is very useful for making your code organizable and readable
class LibEx{
	
	public:  // public items can be interacted with outside of the object
	
	int pDigital;
	int pAnalog; 
	
	// this is a constructor, an optional method, it allows us to bring outside values into the method while its being created.
	// in this example it is taking the value p and assigning that to be an input pin
	LibEx(); // this is a default constructor and will automaticaly be included in your class unless you add a custom one (as seen in line 23)
	LibEx(int p);
	
	// will return the value of the anolog pin assinged
	int GetValue();
	// will send value x HIGH/LOW out on a digital pin
	void OutValue(bool x);
	
	private: // provate items can only be accessed inside this method and will return an error if called outside of it
	int pinVRef;
};

#endif

