
#ifndef StabAlg_h
#define StabAlg_h
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>//M9N
#include "SHC_BNO055.h"

#include "Arduino.h"

enum StabbingDirection {
    CLOCKWISE=1,
    COUNTERCLOCKWISE=-1,
    CLOCKFOOL=0,//thrusters don't turn on
    NOTHING=2,//used for errors, such as when there could be a division by zero
    };


class StabAlg {
private://************PRIVATE**************
    SFE_UBLOX_GNSS& m9n;
    BNO055& bno;
    double timeGoneBy=0;//minutes

    unsigned long previousTime;//milliseconds
    double angularPos;//degrees
    double targetValue=142;//default: estimated azimuth
    double previousError;

    double output;
    double error;//degrees
    double derivative;//degrees per second

    //K values can be adjusted to anything you want
    double Kp=1.5;//experimental value
    double Kd=1;//experimental value

    double deadband=15;//degrees, default value from the bible

public:

    StabAlg(SFE_UBLOX_GNSS&, BNO055&);

    //SFE_UBLOX_GNSS m9n;
    //BNO055 bno;

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