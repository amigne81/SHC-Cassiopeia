
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

    long timeGoneBy;

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

    double previousAngularPos;
    unsigned long previousTime;
    double angularPos;
    double targetValue=0;//true north

    double output;
    double error;
    double derivative;

    double Kp;
    double Kd;

    double deadband=15;//degrees, default value from the bible

};//the devil, from the Bible

#endif