
//orientation -> position
//gyroscope -> velocity
//acceleration -> ...

//normally:
//orientation x -> yaw
//orientation y -> pitch
//orientation z -> roll

//but, because of how the bno is placed:
//orientation X -> yaw
//orientation Y -> pitch
//orientation Z -> roll
//for some reason, nothing changes????

#include "Arduino.h"
#include "StabAlg.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>//M9N
#include "SHC_BNO055.h"

StabAlg::StabAlg(SFE_UBLOX_GNSS& men, BNO055& bro) 
        : m9n(men), bno(bro){
    //m9n = men;//copy of men
    //bno = bro;//copy of bro
                                        //+180 because of BNO placement
    double previousAngularPos = bno.getOrientationX()+180;//Sam? Do I need to run bno.prefetchData()?

    previousError = previousAngularPos-(targetValue+30);//+30 because of camera placement
    while (previousError>180) {
        previousError = previousError-360;
    }
    while (previousError<-180) {
        previousError = previousError+360;
    }//fixing wraparound problem

    previousTime=millis();
}

// Originally, this method was developed for testing purposes, when the M9N was not working
// or when I wanted to assume a constant target. Now, this method has become a backup plan
// in case the M9N failed during flight.
int StabAlg::testRun(double angularPos) {

        //This prevents a division by zero when calculating derivative term
    unsigned long currTime = millis();
    if (currTime==previousTime) {
        return NOTHING;//enough time hasn't gone by for any changes, so thrusters will not turn on
    }

        //Setting up the angularPos and the error term
    // bno.prefetchData();//Sam??? Do I need this here???
    // angularPos = bno.getOrientationX()+180;

    error = angularPos+180-(targetValue+30);
    //Fixing the wraparound problem:
    while (error>180) {
        error = error-360;
    }
    while (error<-180) {
        error = error+360;
    }

        //Setting up the derivative term
    // double deltaDer = error-previousError;
    // //Fixing wraparound problem:
    // while (deltaDer>180) {
    //     deltaDer = deltaDer-360;
    // }
    // while (deltaDer<-180) {
    //     deltaDer = deltaDer+360;
    // }
    // derivative = ((deltaDer)/((currTime-previousTime)));//using seconds, not milliseconds

    derivative=bno.getGyroX();//instead of calculating e'(t), do this

    previousError = error;
    previousTime = currTime;

        //Setting up the control system PD
    output = (Kp * error) + (Kd * derivative);

    // Serial.print("Output: " + String(output));
    // Serial.print(";; Error: " + String(error));
    // Serial.print(";; Der: " + String(derivative));
    // Serial.print(";; angularPos" + String(angularPos));

        //Bang-Bang
    //thruster direction output
    if (output > deadband) {
        // digitalWrite(LED_BUILTIN, LOW);
        return COUNTERCLOCKWISE;
    }
    else if (output < -deadband) {
        // digitalWrite(LED_BUILTIN, LOW);
        return CLOCKWISE;
    }
    // digitalWrite(LED_BUILTIN, HIGH);
    return CLOCKFOOL;//thrusters don't turn on
}

//This method below should be placed in loop() because of the variable timeGoneBy. May work improperly otherwise.
//Note: The target will not change strictly at minuteUpdate minutes. This is fine.
//As long as angularPos gets initalized, we are golden. If not, uh....
int StabAlg::autoTargetRun(double minuteUpdate, double angularPos) {

        //This prevents a division by zero when calculating derivative term
    unsigned long currTime = millis();
    if (currTime==previousTime) {//this prevents a division by zero when calculating derivative term
        return NOTHING;//enough time hasn't gone by for any changes, so thrusters will not turn on/off
    }

        //Checks to see if it is time to update the target
    if (timeGoneBy>=minuteUpdate) {
        targetValue = findNewTarget();

        //angularPos, in this case, would refer to the previous angularPos, as it hasn't updated yet
        previousError = angularPos+180-(targetValue+30);//adjusting the previousError to prevent a sudden jump from target changing
        while (previousError>180) {
            previousError = previousError-360;
        }
        while (previousError<-180) {
            previousError = previousError+360;
        }//fixing wraparound problem

        timeGoneBy = timeGoneBy - ((double) minuteUpdate);//leftover time
    }

        //Setting up the angularPos and the error term
    // bno.prefetchData();//Sam??? Do I need this here?
    // angularPos = bno.getOrientationX()+180;

    error = angularPos+180-(targetValue+30);
    //Fixing wraparound problem    
    while (error>180) {
        error = error-360;
    }
    while (error<-180) {
        error = error+360;
    }

        //Setting up the derivative term
    // double deltaDer = error-previousError;
    // //Fixing wraparound problem
    // while (deltaDer>180) {
    //     deltaDer = deltaDer-360;
    // }
    // while (deltaDer<-180) {
    //     deltaDer = deltaDer+360;
    // }
    // derivative = ((deltaDer)/((currTime-previousTime)));//using seconds, not milliseconds

    derivative=bno.getGyroX();

    previousError = error;
        //Accounting for time gone by
    unsigned long k = previousTime;//accounts for the full interval of time
    previousTime = currTime;

    output = (Kp * error) + (Kd * derivative);

    timeGoneBy += (millis()-k)/60000.0;


    // Serial.println("Output" + String(output));

        //Bang-Bang
    //thruster direction output
    if (output > deadband) {
        // digitalWrite(LED_BUILTIN, LOW);
        return COUNTERCLOCKWISE;
    }
    else if (output < -deadband) {
        // digitalWrite(LED_BUILTIN, LOW);
        return CLOCKWISE;
    }
    // digitalWrite(LED_BUILTIN, HIGH);
    return CLOCKFOOL;//thrusters don't turn on
}

//Note: The math below runs accurately enough
double StabAlg::findNewTarget() {
    //Sam?? Do I need a m9n.prefetchData() here? That method doesn't exist..

    int day = 298;//october 25th, 2026 (not a leap year); launch day

    // testing values if the M9N does not work
    // int hour = 9;
    // int min = 30;
    // double latitude = 36.0669;
    // double longitude = -88.8179;

    //actial values from the M9N
    int hour = m9n.getHour();
    int min = m9n.getMinute();
    double latitude = m9n.getLatitude()*0.0000001;//degrees
    double longitude = m9n.getLongitude()*0.0000001;//degrees
    
    //int GHT = -5;//Central Daylight Time
    int GHT = 0;//the M9N uses UTC as its time zone :(

    double latitudeRad = latitude * PI / 180.0;

    double fractionalYear = ( (2*PI)/365 ) * (day-1 + ( (hour-12)/24.0 ) + (min/1440.0));

    double cosFY = cos(fractionalYear);
    double sinFY = sin(fractionalYear);
    double cos2FY = cos(2 * fractionalYear);
    double sin2FY = sin(2 * fractionalYear);
    
    double equationOfTime = //Equation of Time; Spencer approximation
            229.18 * (
            0.000075
            + 0.001868 * cosFY
            - 0.032077 * sinFY
            - 0.014615 * cos2FY
            - 0.040849 * sin2FY);

    double declinationRad =
          0.006918
        - 0.399912 * cosFY
        + 0.070257 * sinFY
        - 0.006758 * cos2FY
        + 0.000907 * sin2FY
        - 0.002697 * cos(3 * fractionalYear)
        + 0.001480 * sin(3 * fractionalYear);//radians
    
    double timeOffSet = equationOfTime + (4*longitude) - (60*GHT);

    double trueSolarTime = (60*hour) + min + timeOffSet;//minutes

    double sunHourAngleDeg = (trueSolarTime/4) - 180;//degrees
    double sunHourAngleRad = sunHourAngleDeg * PI / 180.0;//radians

    double azimuthRad = //range: -pi to pi
        atan2(-sin(sunHourAngleRad),
        tan(declinationRad)*cos(latitudeRad)-sin(latitudeRad)*cos(sunHourAngleRad));
    
    double azimuthDeg = (azimuthRad * 180.0) / PI;
    if (azimuthDeg < 0) //to deal with the range that atan2 gives us
        azimuthDeg += 360.0;

    return azimuthDeg;
}

//The method below tells the solenoids what to do
void StabAlg::solenoidTranslate(int instruction) {    
    Serial.println(instruction);

    if (instruction==CLOCKWISE) {//turn on 'right' solenoid
        digitalWrite(3,LOW);
        digitalWrite(4,HIGH);
        Serial.println("wise");
    }
    else if (instruction==COUNTERCLOCKWISE) {//turn on 'left' solenoid
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        Serial.println("counter");
    }
    else if (instruction==NOTHING) {//do nothing. Even the solenoids aren't being turned off        
        Serial.println("nothing");
    }
    else {//instruction==CLOCKFOOL -> turn everything off
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        Serial.println("fool");
    }
}

//Moves the solenoids based on adjusting target
void StabAlg::update(double min, double angularPos) {

    if(m9n.getSIV()<=2) {
        solenoidTranslate(testRun(angularPos));
        Serial.println("M9N Satellite Problem - StabAlg");
    }
    else {
        solenoidTranslate(autoTargetRun(min, angularPos));//(recommended 10 min)
    }
}

//Moves the solenoids based on constant target
void StabAlg::updateTestRun(double angularPos) {
    solenoidTranslate(testRun(angularPos));
}

//***********************SETTERS
void StabAlg::setTarget(double value) {
    while (value<0) {
        value=value+360;
    }
    while (value>=360) {
        value=value-360;
    }

    targetValue=value;
}
void StabAlg::setKp(double value) {
    Kp=value;
}
void StabAlg::setKd(double value) {
    Kd=value;
}
void StabAlg::setDeadband(double value) {
    deadband=abs(value);
}

//********************GETTERS
double StabAlg::getAngularPos() {
    return angularPos;
}
double StabAlg::getTarget() {
    return targetValue;
}
double StabAlg::getKp() {
    return Kp;
}
double StabAlg::getKd() {
    return Kd;
}
double StabAlg::getDeadband() {
    return deadband;
}
