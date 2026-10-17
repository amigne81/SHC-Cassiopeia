
#include "Arduino.h"
#include "StabAlg.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>//M9N

//#include "SHC_BNO055.h"

void Stabinit();
void Stabtest();


//SFE_UBLOX_GNSS m9n = SFE_UBLOX_GNSS();
BNO055 ghj = BNO055();
//StabAlg stab = StabAlg(m9n, bno);
StabAlg stab = StabAlg(ghj);

void setup() {//I'm pretty sure I was supposed to make a seperate testing environment? Hopefully this is ok...
    //stuff, like Wire.begin(), pinMode, Sereal.begin(9600), ...
    Wire.begin();
    Serial.begin(9600);

    ghj.init();
    
}

void loop() {

    
    ghj.prefetchData();
//     Serial.print("Accel: (" + String(ghj.getAccelerationX()));
//   Serial.print(", " + String(ghj.getAccelerationY()));
//   Serial.println(", " + String(ghj.getAccelerationZ()) + ")");
//   Serial.print("Gyro: (" + String(ghj.getGyroX()));
//   Serial.print(", " + String(ghj.getGyroY()));
//   Serial.println(", " + String(ghj.getGyroZ()) + ")");
  Serial.print("Orient: (" + String(ghj.getOrientationX()));
//   Serial.print(", " + String(ghj.getOrientationY()));
//   Serial.println(", " + String(ghj.getOrientationZ()) + ")");
    // delay(1000);

    // Serial.println(stab.testRun());

    // digitalWrite(3, HIGH);
    // delay(100);
    // digitalWrite(3, LOW);

    // digitalWrite(4, HIGH);
    // delay(100);
    // digitalWrite(4, LOW);

    //Serial.println("running?");


    //Testing Solenoids
    int instruction = stab.testRun();

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
    else if (instruction==2) {

    }
    else {//instruction==CLOCKFOOL -> turn everything off
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        Serial.println("fool");
    }

    Serial.println(stab.getAngularPos());

    delay(5);
    


    // //Testing Target Value
    // Serial.print("Target value: ");
    // Serial.println(stab.findNewTarget());

    // Serial.println("\n Dirrection: ");
    // Serial.println(stab.testRun());

    // Serial.println("\n Hour: ");
    // Serial.println(m9n.getHour());

    // Serial.println("\n Minute: ");
    // Serial.println(m9n.getMinute());
}


void Stabinit() {


}

void Stabtest() {


}