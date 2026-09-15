//must include arduino and the header file
#include "Arduino.h";
#include "LED.h";

//constructor
LED::LED(int p){
    bool state = false;
    int pinNum = p;

    pinMode(pinNum, OUTPUT)     //sets the pin the LED is on to be an output, or controllable
}

bool LED::toggle(){
    if !state{
        on();
        return true;
    }
    else{
        off();
        return false;
    }
}

void on(){
    digitalWrite(pinNum, HIGH);
}

void off(){
    digitalWrite(pinNum, LOW);
}        

void flashRetrieval(){
    on();
    delay(1000);
    off();
    delay(1000);
}

bool getState(){
    if state{
        return true;
    }
    else{
        return false;
    }
}  