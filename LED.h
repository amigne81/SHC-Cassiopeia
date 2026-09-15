//checks to see if there is already an instance of this file
//if there is stop, dont run, it will break
#ifndef LED_h;
#define LED_h;

//includes the arduino functions
#include "Ardunio.h";


class LED{

    //must define scope
    public:

    //defualt contructor for LED pin, takes 1 int for the pin number
    LED(int p);

    //meathods
    bool toggle();        //will toggle LED and return the state of the LED
    void on();            //will turn on LED
    void off();           //will turn off LED
    void flashRetrieval() //will flash lights at regular intervals for retrieval
    bool getState();      //will return the state of the LED

    private:
    bool state;
    
}

#endif