
#include "Arduino.h"
#include "StabAlg.h"

StabAlg::StabAlg(double firstAngularPos) {
    zeroAngularPos=firstAngularPos;
    startTime = millis();
}

//is there is an error, check for missing pre-fetch.
//if you don't know what that is, ask Sam :D
//This method is where you can adjust the targetValue
long StabAlg::testRun() {

    angularPos = BNO.getOrientationX();

    error = targetValue-angularPos;

    derivative = (targetValue - (angularPos-zeroAngularPos) )/(millis()-startTime);//also known as the angular velocity
    zeroAngularPos = angularPos;

    output = (Kp * error) + (Kd * derivative);

    if (output > deadband) {
        return CLOCKWISE;
    }
    else if (output < -deadband) {
        return COUNTERCLOCKWISE;
    }
    return CLOCKFOOL;//thrusters don't turn on
}

//This method below should be placed in loop() because of the variable timeGoneBy. May work improperly otherwise.
long StabAlg::autoTargetRun(unsigned long millisecondUpdate) {
    unsigned long updateTime = 0.001*millisecondUpdate;//minutes

    if (timeGoneBy>=updateTime) {
        targetValue = findNewTarget();
        timeGoneBy = 0;
    }

    angularPos = BNO.getOrientationX();

    error = targetValue-angularPos;

    derivative = (targetValue - (angularPos-zeroAngularPos) )/(millis()-startTime);//also known as the angular velocity
    zeroAngularPos = angularPos;

    output = (Kp * error) + (Kd * derivative);

    timeGoneBy += (millis()-startTime);

    if (output > deadband) {
        return CLOCKWISE;
    }
    else if (output < -deadband) {
        return COUNTERCLOCKWISE;
    }
    return CLOCKFOOL;//thrusters don't turn on
}

//NOTE: THE BELOW CODE IS SET TO RUN ON 10/25/26. FOR TESTING, MAY NEED TO ADJUST VALUES
double StabAlg::findNewTarget() {
    int day = 298;//october 25th, 2026 (not a leap year); launch day
    int hour = M9N.getHour();
    int min = M9N.getMinute();
    double latitude = M9N.getLatitude();//degrees
    double longitude = M9N.getLongitude();//degrees
    int GHT = 5;//Central Daylight Time

    double latitudeRad = latitude * PI / 180.0;

    double fractionalYear = ( (2*PI)/365 ) * (day-1 + ( (hour-12)/24.0 ));
    
    double equationOfTime = //Equation of Time; Spencer approximation
            229.18 * (
            0.000075
            + 0.001868 * cos(fractionalYear)
            - 0.032077 * sin(fractionalYear)
            - 0.014615 * cos(2 * fractionalYear)
            - 0.040849 * sin(2 * fractionalYear)
        );

    double declinationRad =
          0.006918
        - 0.399912 * cos(fractionalYear)
        + 0.070257 * sin(fractionalYear)
        - 0.006758 * cos(2 * fractionalYear)
        + 0.000907 * sin(2 * fractionalYear)
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
void StabAlg::setAngularPos(double value) {
    angularPos=value;
}
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
