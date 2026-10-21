
#include "Arduino.h"
#include "StabAlg.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>//M9N

//#include "SHC_BNO055.h"

void Stabinit();
void Stabtest();


SFE_UBLOX_GNSS tyu = SFE_UBLOX_GNSS();
BNO055 ghj = BNO055();
StabAlg stab = StabAlg(tyu, ghj);
const int Orientation_delay = 50;//ms

void setup() {
    Wire.begin();
    Serial.begin(9600);

    ghj.init();//bno

}

void loop() {
    // ghj.prefetchData();

    stab.update(10);
    delay(25);

    // solenoidTransalte();
}

void testSolenoids() {
    delay(1000);

    digitalWrite(3, HIGH);
    delay(100);
    digitalWrite(3, LOW);

    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(4, LOW);
}

void testTargetValueInfo() {
    //Testing Target Value
    Serial.print("Target value: ");
    Serial.println(stab.findNewTarget());

    Serial.println("\n Dirrection: ");
    Serial.println(stab.testRun());

    Serial.println("\n Hour: ");
    Serial.println(tyu.getHour());

    Serial.println("\n Minute: ");
    Serial.println(tyu.getMinute());
}

void testOrientation() {

    //   Serial.print("Accel: (" + String(ghj.getAccelerationX()));
    //   Serial.print(", " + String(ghj.getAccelerationY()));
    //   Serial.println(", " + String(ghj.getAccelerationZ()) + ")");
    //   Serial.print("Gyro: (" + String(ghj.getGyroX()));
    //   Serial.print(", " + String(ghj.getGyroY()));
    //   Serial.println(", " + String(ghj.getGyroZ()) + ")");
      Serial.print("Orient: (" + String(ghj.getOrientationX()));
    //   Serial.print(", " + String(ghj.getOrientationY()));
    //   Serial.println(", " + String(ghj.getOrientationZ()) + ")");
}

void solenoidsTranslate(int instruction) {    
    //Running the test to see if the payload spins correctly
    // int instruction = update();//stab.testRun();

    if (instruction==CLOCKWISE) {//turn on 'right' solenoid???
        digitalWrite(3,LOW);
        digitalWrite(4,HIGH);
        Serial.println("clockwise");
    }
    else if (instruction==COUNTERCLOCKWISE) {//turn on 'left' solenoid???
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        Serial.println("counter");
    }
    else if (instruction==2) {//do nothing. Even the solenoids aren't being turned off        
        Serial.println("nothing");
    }
    else {//instruction==CLOCKFOOL -> turn everything off
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        Serial.println("fool");
    }

    Serial.println(stab.getAngularPos());

    //delay(50);//for testing, we will use delay. For the flight code, don't
}