//must include arduino and the header file
#include <Arduino.h>
#include "LED.h"


//constructor
LED::LED(int p){
    isOn = false;
    pinNum = p;

    pinMode(pinNum, OUTPUT);     //sets the pin the LED is on to be an output, or controllable
}

//toggles the LED and returns the state
bool LED::toggle(){
    if (!isOn){
        on();
    }
    else{
        off();
    }
    return isOn;
}

//turns on LED and edits state to on
void LED::on(){
    digitalWrite(pinNum, HIGH);
    isOn = true;
}

//turns off LED and edits state to off
void LED::off(){
    digitalWrite(pinNum, LOW);
    isOn = false;
}        

//returns the state of the LED
bool LED::getState(){
    return isOn;
}  