
#include "Arduino.h"
#include "StabAlg.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>//M9N
#include "SHC_BNO055.h"

void Stabtest();

SFE_UBLOX_GNSS MMM = SFE_UBLOX_GNSS();//M9N
BNO055 BBB = BNO055();//BNO
StabAlg stab = StabAlg(MMM, BBB);
const int Orientation_delay = 50;//ms

void setup() {
    Wire.begin();
    Serial.begin(9600);

    BBB.init();//bno uses SHC
}

void loop() {
    // ghj.prefetchData();

    Stabtest();
    // stab.update(10);
}

void testSolenoids() {
    delay(1000);

    digitalWrite(3, HIGH);
    delay(100);
    digitalWrite(3, LOW);

    delay(1000);

    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(4, LOW);
}

void testTargetValueInfo() {
    //Testing Target Value
    Serial.print("Target value: ");
    Serial.println(stab.findNewTarget());

    Serial.println("\n Dirrection: ");
    Serial.println(stab.autoTargetRun(10));

    Serial.println("\n Hour: ");
    Serial.println(MMM.getHour());

    Serial.println("\n Minute: ");
    Serial.println(MMM.getMinute());
}

//The below test simulates update(), the method that will be used during flight
void Stabtest() {//adjusts the targetValue to see that nothing breaks. Yes, it uses delay(), trust

  delay(1000);

  stab.setTarget(0);
  stab.updateTestRun();
  delay(25);
  stab.updateTestRun();

  delay(1500);

  stab.setTarget(45);
  stab.updateTestRun();
  delay(25);
  stab.updateTestRun();

  delay(1500);

  stab.setTarget(90);
  stab.updateTestRun();
  delay(25);
  stab.updateTestRun();

  delay(1500);

  stab.setTarget(45);
  stab.updateTestRun();
  delay(25);
  stab.updateTestRun();

  delay(1500);

  stab.setTarget(0);
  stab.updateTestRun();
  delay(25);
  stab.updateTestRun();
}

void testOrientation() {

    //   Serial.print("Accel: (" + String(BBB.getAccelerationX()));
    //   Serial.print(", " + String(BBB.getAccelerationY()));
    //   Serial.println(", " + String(BBB.getAccelerationZ()) + ")");
    //   Serial.print("Gyro: (" + String(BBB.getGyroX()));
    //   Serial.print(", " + String(BBB.getGyroY()));
    //   Serial.println(", " + String(BBB.getGyroZ()) + ")");
      Serial.print("Orient: (" + String(BBB.getOrientationX()));
    //   Serial.print(", " + String(BBB.getOrientationY()));
    //   Serial.println(", " + String(BBB.getOrientationZ()) + ")");
}