#include <Arduino.h>
#include "LED.h"
#include <SHC_BME280.h>

// put function declarations here:
int myFunction(int, int);
LED light = LED(3);


void setup() {
  // put your setup code here, to run once:
light = LED(3);
Serial.begin(9600);
Serial.println("Started!");
}

void loop() {
  // put your main code here, to run repeatedly:
  light.toggle();
  delay(1000);
  Serial.println("hello");
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}