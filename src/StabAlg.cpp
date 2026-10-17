
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

#include "Arduino.h"
#include "StabAlg.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>//M9N
#include "SHC_BNO055.h"

StabAlg::StabAlg(BNO055 bro) {//SFE_UBLOX_GNSS men, BNO055 bro
    //m9n = men;
    bno = bro;

    double previousAngularPos = bno.getOrientationX();
    // double previousAngularPos = 340;//remove after testing
    // angularPos = 180;//remove after testing

    previousError = previousAngularPos-targetValue;
    if (previousError>180) {
        previousError = previousError-360;
    }
    else if (previousError<-180) {
        previousError = previousError+360;
    }//fixing wraparound problem

    previousTime=millis();
}

//is there is an error, check for missing pre-fetch.
//if you don't know what that is, ask Sam :D
//This method is where you can adjust the targetValue
int StabAlg::testRun() {

    unsigned long currTime = millis();
    if (currTime==previousTime) {//I truly don't believe this will ever execute, but I don't want to risk it
        Serial.println("Please don't");
        return 2;//enough time hasn't gone by for any changes, so thrusters will not turn on
        
    }
    bno.prefetchData();
    angularPos = bno.getOrientationX();

    error = angularPos-targetValue;
    if (error>180) {
        error = error-360;
    }
    else if (error<-180) {
        error = error+360;
    }//fixing wraparound problem

    double deltaDer = error-previousError;
    if (deltaDer>180) {
        deltaDer = deltaDer-360;
    }
    else if (deltaDer<-180) {
        deltaDer = deltaDer+360;
    }//fixing wraparound problem
    derivative = ((deltaDer)/(currTime-previousTime))*1000;//using seconds, not milliseconds

    previousError = error;
    previousTime = currTime;

    output = (Kp * error) + (Kd * derivative);

    //thruster direction output
    if (output > deadband) {
        return COUNTERCLOCKWISE;
    }
    else if (output < -deadband) {
        return CLOCKWISE;
    }
    return CLOCKFOOL;//thrusters don't turn on
}

//This method below should be placed in loop() because of the variable timeGoneBy. May work improperly otherwise.
//Note: The target will not change strictly at minuteUpdate minutes. This is fine.
//As long as angularPos gets initalized, we are golden. If not, uh....
int StabAlg::autoTargetRun(unsigned long minuteUpdate) {

    unsigned long currTime = millis();
    if (currTime==previousTime) {//I truly don't believe this will ever execute, but I don't want to risk it
        return CLOCKFOOL;//enough time hasn't gone by for any changes, so thrusters will not turn on
    }

    if (timeGoneBy>=minuteUpdate) {
        targetValue = findNewTarget();

        //angularPos, in this case, would refer to the previous angularPos, as it hasn't updated yet
        previousError = angularPos-targetValue;//adjsuing the previousError to prevent a sudden jump from target changing
        if (previousError>180) {
            previousError = previousError-360;
        }
        else if (previousError<-180) {
            previousError = previousError+360;
        }//fixing wraparound problem

        timeGoneBy = timeGoneBy- ((double) minuteUpdate);//leftover time
    }

    angularPos = bno.getOrientationX();

    error = angularPos-targetValue;
    if (error>180) {
        error = error-360;
    }
    else if (error<-180) {
        error = error+360;
    }//fixing wraparound problem

    
    double deltaDer = error-previousError;
    if (deltaDer>180) {
        deltaDer = deltaDer-360;
    }
    else if (deltaDer<-180) {
        deltaDer = deltaDer+360;
    }//fixing wraparound problem
    derivative = ((deltaDer)/(currTime-previousTime))*1000;//using seconds, not milliseconds

    previousError = error;

    unsigned long k = previousTime;
    previousTime = currTime;

    output = (Kp * error) + (Kd * derivative);

    timeGoneBy += (millis()-k)/60000.0;

    //thruster direction output
    if (output > deadband) {
        return COUNTERCLOCKWISE;
    }
    else if (output < -deadband) {
        return CLOCKWISE;
    }
    return CLOCKFOOL;//thrusters don't turn on
}

//Note: The math below runs well enough -Alexander
double StabAlg::findNewTarget() {
    int day = 298;//october 25th, 2026 (not a leap year); launch day
    //int hour = m9n.getHour();
    //int min = m9n.getMinute();
    int hour = 9;
    int min = 30;
    // double latitude = m9n.getLatitude();//degrees
    // double longitude = m9n.getLongitude();//degrees
    double latitude = 36.0669;
    double longitude = -88.8179;
    //int GHT = -5;//Central Daylight Time
    int GHT = 0;//the M9N uses UTC as its time zone :(

    double latitudeRad = latitude * PI / 180.0;

    double fractionalYear = ( (2*PI)/365 ) * (day-1 + ( (hour-12)/24.0 ) + (min/1440));

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
            - 0.040849 * sin2FY
        );

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

//***********************SETTERS
void StabAlg::setTargetValue(double value) {
    targetValue=value;
}
void StabAlg::setKp(double value) {
    Kp=value;
}
void StabAlg::setKd(double value) {
    Kd=value;
}
void StabAlg::setDeadband(double value) {
    deadband=value;
}

//********************GETTERS
double StabAlg::getAngularPos() {
    return angularPos;
}
double StabAlg::getTargetValue() {
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
