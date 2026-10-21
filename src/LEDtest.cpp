#include "LED.cpp"

LED light = LED(2);
int buzzerPin = 5;

void chirp(int);

void setup(){
    LED light = LED(2);
    buzzerPin = 5;
}

void loop(){
    light.toggle();
    Serial.println(light.getState());
    delay(1000);

    chirp(buzzerPin);
    delay(500);    
    chirp(buzzerPin);
    delay(500);
    chirp(buzzerPin);
    delay(10000);
}

void chirp(int pin){
    Serial.println("buzz");

  for(int i = 0; i < 400; i++){
        digitalWrite(pin,HIGH);
        delayMicroseconds(i);
        digitalWrite(pin,LOW);
        delayMicroseconds(i);
    } 
    for(int i = 400; i > 0; i--){
        digitalWrite(pin,HIGH);
        delayMicroseconds(i);
        digitalWrite(pin,LOW);
        delayMicroseconds(i);
    } 
}
