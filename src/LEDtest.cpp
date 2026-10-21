#include "LED.cpp"

LED light = LED(2);

void setup(){
    LED light = LED(2);
}

void loop(){
    light.toggle();
    Serial.println(light.getState());
    delay(1000);
}