
#include "Arduino.h";
#include "LibEx.h";
// this is the second and more common way to write a comment and will set the whole line to a comment!

// the part before the (::) tells the program that this is an object from the LibEx class
//
// the Second part tells the computer that this is a constructor: 
// constructors are only called once when the object is created amd allow you to customize your class objects.
// constuctors must have the same name as your class or the compiler will this it is a regular method and it wont work.
// to create a class object of this class you would write libEx(your number here);
LibEx::LibEx(){
	int pDigital = 2;
	int pAnalog  = A1;
	pinMode(pDigital,OUTPUT);
	pinMode(pAnalog,INPUT);
}

// our java coders may rememeber the super() function, this has no c++ equivalent and you will have to repeat it for each constructor
LibEx::LibEx(int p){
	int pDigital = 2;
	int pAnalog  = A1;
	pinMode(pDigital,OUTPUT);
	pinMode(pAnalog,INPUT);
}	

// notice how the second word in this function is capitalized  :O
// this is called Camel Case and we will use it to differentiate between variables, methods, and classes/structures, it also makes your words legible (yay!)
int LibEx::GetValue(){
	return analogRead(pAnalog);
}

void LibEx::OutValue(bool x){
	if(x){
		digitalWrite(pDigital, HIGH);
	}else
		digitalWrite(pDigital,LOW);
}