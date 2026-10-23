#ifndef StabAlgPlanB_h
#define StabAlgPlanB_h
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>//M9N
#include "SHC_BNO055.h"

#include "Arduino.h"

enum StabbingDirection {
    CLOCKWISE=1,
    COUNTERCLOCKWISE=-1,
    CLOCKFOOL=0,//thrusters don't turn on
    NOTHING=2,//used for errors, such as when there could be a division by zero
    };


class StabAlgPlanB {
private://************PRIVATE**************
    double timeGoneBy=0;//minutes

    unsigned long previousTime=-1;//milliseconds
    double angularPos;//degrees
    double targetValue=0;//default: true north
    double previousError;

    int hour;
    int min;
    int latitude;
    int longitude;

    double output;
    double error;//degrees
    double derivative;//degrees per second

    //K values can be adjusted to anything you want
    double Kp=1.5;//experimental value
    double Kd=1;//experimental value

    double deadband=15;//degrees, default value from the bible

public:

    StabAlgPlanB(double);

    void setValues(double, int, int, double, double);

    int testRun();//returns 1-> GO CLOCK; -1-> GO COUNTER; 0-> DO NOTHING
    int autoTargetRun(double);//similar to testRun, just auto changes the targetValue every inputted positive minutes

    void setTarget(double);
    double getAngularPos();
    double getTarget();

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
    
};//the devil, from the Bible

#endif