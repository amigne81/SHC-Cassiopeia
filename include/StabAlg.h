
#ifndef StabAlg_h
#define StabAlg_h
#include "SHC_M9N.h"
#include "SHC_BNO055.h"

#include "Arduino.h";

enum StabbingDirection {
    CLOCKWISE=1,
    COUNTERCLOCKWISE=-1,
    CLOCKFOOL=0,//thrusters don't turn on
};


class StabAlg {

    public:

    StabAlg(M9N, BNO055);

    M9N m9n;
    BNO055 bno;

    long testRun();//returns 1-> GO CLOCK; -1-> GO COUNTER; 0-> DO NOTHING
    long autoTargetRun(unsigned long);//similar to testRun, just auto changes the targetValue every inputted milliseconds

    void setAngularPos(double);
    void setTargetValue(double);
    double getAngularPos();
    double getTargetValue();

    void setKp(double);
    void setKd(double);
    double getKp();
    double getKd();

    void setDeadband(double);
    double getDeadband();

    private://************PRIVATE**************

    double findNewTarget();

    long timeGoneBy;//milliseconds

    double previousAngularPos;//degrees
    unsigned long previousTime;//milliseconds
    double angularPos;//degrees
    double targetValue=0;//default: true north

    double output;
    double error;//degrees
    double derivative;//degrees per second

    //K values can be adjusted to anything you want
    double Kp=1;
    double Kd=1;

    double deadband=15;//degrees, default value from the bible

};//the devil, from the Bible

#endif