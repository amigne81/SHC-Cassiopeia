
#ifndef StabAlg_h
#define StabAlg_h

#include "Arduino.h";

class StabAlg {

    public:

    StabAlg(long);//takes the first angular position

    long run();//returns 1-> GO CLOCK, -1-> GO COUNTER, 0-> DO NOTHING

    void setAngularPos(long);
    void setTargetValue(long);
    long getAngularPos();
    long getTargetValue();

    void setKp(double);
    void setKd(double);
    double getKp();
    double getKp();

    void setDeadband(double);
    double getDeadband();

    private://************PRIVATE**************

    long zeroAngularPos;
    long angularPos;
    long targetValue;

    long output;
    long error;
    long derivative;

    double Kp;
    double Kd;

    double deadband=15;//degrees

    bool clockwise(long output);
    bool counterclockwise(long output);
};

#endif