#include <Arduino.h>
#include "LED.h"
// put function declarations here:
int myFunction(int, int);
LED light = LED(3);


void setup() {
  // put your setup code here, to run once:
light = LED(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  light.toggle();
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}