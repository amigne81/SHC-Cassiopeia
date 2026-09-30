
#include "Arduino.h"
#include "StabAlg.h"

StabAlg::StabAlg(double firstAngularPos) {
    zeroAngularPos=firstAngularPos;
    startTime = millis();
}

//is there is an error, check for missing pre-fetch.
//if you don't know what that is, as Sam :D
long StabAlg::run() {

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
    return CLOCKFOOL;
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
