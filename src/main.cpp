#include <Arduino.h>
#include "LED.h"
#include "Clock.h"
#include "Data.h"
#include "StabAlg.h"
#include "string"
#include <SHC_BME280.h>


// global object initalization
Data rec;
StabAlg stabilize;
LED LED1(-1), LED2(-1);

// global variable intialization
const int target_altitude = 20000;
const int standby_thresh = 1;
const int standby_exit_mod = 8; 
const int emergency_standby_exit= 5000;
const unsigned long int UTC_Time;
int nError = 0;

// time duration requiredments to switch states in milliseconds: to target alt, to descent, to standby
const unsigned long int tReq[3] = {20000,30000,60000};

// function declariation
void below_target();
void target_alt();
void descent();
void standby();
void output();
void setData();
int stateCheck();

void setup() {
Serial.begin(9600);
Serial.println("Started!");
rec.time.setUTC(UTC_Time);

}

void loop() {
  rec.state = stateCheck();

  switch(rec.state){
    case 0:
      below_target();
    case 1:
      target_alt();
    case 2:
      descent();
    case 3:
      standby();
    default:
      nError++;
  }

}

void below_target(){

}

void target_alt(){

}

void descent(){

}

void standby(){
  
}



void output(){
  //Serial.print(rec.outCSV()); // replace -1 w/ current time from rework clock function
}

int stateCheck(){
  static unsigned long int dur[4];
  unsigned long int dt = rec.time.dt();
  int dh = rec.getDh();
  int h = rec.getH();
  // checks values based on state: can move forward only one state at a time 
  switch(rec.state){
    case 0: // ascent to target alt
      if(h >= target_altitude){
        dur[0] += dt;
      }else{dur[0]=0; dur[1]=0; dur[2] = 0;}

    case 1: // target alt to descent
      if(dh<0){
        dur[1]+= dt;
      }else if(h < target_altitude){  // revert chack to state ascent
        dur[1] = 0;
        dur[0] += dt;
      }else{dur[0]=0; dur[1]=0; dur[2] = 0;}

    case 2: // descent to standby
      if(dh > standby_thresh || dh < -standby_thresh){
        dur[2] += dt;
      }else if(dh<0){ // revert check to descent
        dur[1] += dt;
        if(dur[1] > dt*standby_exit_mod) // because negative dh could be higher than expected while in standby it must be continous for longer to reset progress towards standby
          dur[2] = 0;
      }else{dur[0]=0; dur[1]=0; dur[2] = 0;}

    case 3: // standby operates seperate from others and only goes to target altitude
      if(h > target_altitude){
        dur[3] += dt;
      }else{dur[3]=0;}
      if(dur[3] >= emergency_standby_exit){
        return 1;
      }
  }

  for(int i = 2; i>=0;i--){
    if(dur[i]>tReq[i]){ // prioritizes highest state 
      return i;
    }
  }

}
