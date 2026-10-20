

#include <Arduino.h>
 
int chirpPin = 5;
int rnd = 500;
 
void setup()
{
  Serial.begin(9600);
 
  pinMode(chirpPin, OUTPUT);
}
 
 
void loop()
{
    //tone(5,1000);
    for(int i = 0; i < 400; i++){
        digitalWrite(chirpPin,HIGH);
        delayMicroseconds(i);
        digitalWrite(chirpPin,LOW);
        delayMicroseconds(i);
    } 
    for(int i = 400; i > 0; i--){
        digitalWrite(chirpPin,HIGH);
        delayMicroseconds(i);
        digitalWrite(chirpPin,LOW);
        delayMicroseconds(i);
    } 
    /*
    for(int i = 0; i < 200; i++){
        digitalWrite(chirpPin,HIGH);
        delayMicroseconds(i);
        digitalWrite(chirpPin,LOW);
        delayMicroseconds(i);
    } 
    for(int i = 300; i > 0; i--){
        digitalWrite(chirpPin,HIGH);
        delayMicroseconds(i);
        digitalWrite(chirpPin,LOW);
        delayMicroseconds(i);
    } 
    */

    rnd = 1000 + random(3000);
    delay(rnd);
}
