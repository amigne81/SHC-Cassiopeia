//must include arduino and the header file
#include "Arduino.h"
#include "LED.h"

//constructor
LED::LED(int p){
    bool state = false;
    int pinNum = p;

    pinMode(pinNum, OUTPUT)     //sets the pin the LED is on to be an output, or controllable
}

bool LED::toggle(){
    if !state{
        on();
    }
    else{
        off();
    }
    return state;
}

void LED::on(){
    digitalWrite(pinNum, HIGH);
    state = true;
}

void LED::off(){
    digitalWrite(pinNum, LOW);
    state = false;
}        

void LED::flashRetrieval(){
    toggle();
    delay(1000);
}

bool :ED::getState(){
    return state;
}  