
#ifndef StabAlg_h
#define StabAlg_h
#include "SHC_M9N.h"
#include "SHC_BNO055.h"

#include "Arduino.h"

enum StabbingDirection {
    CLOCKWISE=1,
    COUNTERCLOCKWISE=-1,
    CLOCKFOOL=0,//thrusters don't turn on
    NOTHING=2,//used for errors, such as when there could be a division by zero
    };


class StabAlg {

    public:

    StabAlg(SFE_UBLOX_GNSS, BNO055);

    SFE_UBLOX_GNSS m9n;
    BNO055 bno;

    int testRun();//returns 1-> GO CLOCK; -1-> GO COUNTER; 0-> DO NOTHING
    int autoTargetRun(unsigned long);//similar to testRun, just auto changes the targetValue every inputted minutes

    void setTargetValue(double);
    double getAngularPos();
    double getTargetValue();

    void setKp(double);
    void setKd(double);
    double getKp();
    double getKd();

    void setDeadband(double);
    double getDeadband();

    double findNewTarget();

    void update(double);
    void updateTestRun();
    void solenoidTranslate(int);
    

    private://************PRIVATE**************

    double timeGoneBy=0;//minutes

    unsigned long previousTime;//milliseconds
    double angularPos;//degrees
    double targetValue=0;//default: true north
    double previousError;

    double output;
    double error;//degrees
    double derivative;//degrees per second

    //K values can be adjusted to anything you want
    double Kp=1.5;//experimental value
    double Kd=1;//experimental value

    double deadband=15;//degrees, default value from the bible
};//the devil, from the Bible

#endif