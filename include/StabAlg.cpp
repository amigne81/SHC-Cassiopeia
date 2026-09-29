
#include "Arduino.h"
#include "StabAlg.h"

StabAlg::StabAlg(long firstAngularPos) {
    zeroAngularPos=firstAngularPos;
}

long StabAlg::run() {

    error = targetValue-angularPos;

    derivative = (targetValue - (angularPos-zeroAngularPos) )/(timePerRun);//also known as the angular velocity
    zeroAngularPos = angularPos;

    output = (Kp * error) + (Kd * derivative);

    if (clockwise(output)) {
        return 1;
    }
    else if (counterclockwise(output)) {
        return -1;
    }
    return 0;
}