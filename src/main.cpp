#include <Arduino.h>
#include <Utils.h>
#include <Wire.h>
#include "LED.h"
#include "Clock.h"
#include "Data.h"
#include "StabAlg.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
//#include <SHC_M9N.h>
#include <SHC_BME280.h>
#include <Adafruit_BMP3XX.h>
//#include <Adafruit_INA260.h>

//    sensors
SFE_UBLOX_GNSS hotMenInYourArea = SFE_UBLOX_GNSS();
//M9N hotMenInYourArea;
BNO055 gayDar = BNO055();             // adafruit preset (55, 0x28, &Wire)
SHC_BME280 guy = SHC_BME280();
Adafruit_BMP3XX dude = Adafruit_BMP3XX();
//Adafruit_INA260 power;

// global object initalization
Data rec;
StabAlg TheUK = StabAlg(hotMenInYourArea, gayDar);
LED LED1(-1), LED2(-1); 



// global variable intialization
const int solenoid_pin1 = 3;
const int solenoid_pin2 = 4;
const int buzzerPin = 5;

const int attempt_num = 100;        // number of attempts made before giving up on sensor
const int target_altitude = 20000;
const int standby_thresh = 1;
const int standby_exit_mod = 8; 
int nError = 0;
bool erMen = true, erGay = true, erGuy = true, erDude = true, erPower = true;

// time duration requiredments to switch states in milliseconds: to target alt, to descent, to standby
const unsigned long int tReq[3] = {20000,30000,60000};
const int emergency_standby_exit= 5000; // time to exit if in target alt while in standby state (milliseconds)
const int attempt_delay = 150; // delay between attempts of sensor initialization
const int led_delay = 160;    // delay is between flashes, duration is the length of flashes
const int led_duration = 40;
const int standby_delay = 3000;

unsigned long startTimeUK;

// function declariation
void below_target();
void target_alt();
void descent();
void standby();
void output();
void setData();
void recSensors();
void setupSensors();
void blink();
// stabilize test copy
void Stabinit();
void Stabtest();
void testSolenoids();
void testTargetValueInfo();
void testOrientation();
void solenoidsTranslate(int);
void chirp(int);

int stateCheck();

void setup() {


  Serial.begin(9600);
  delay(750);
  Serial.println("Program start0\n");
  delay(750);
  Serial1.begin(9600);
  delay(750);
  Serial1.println("Program start\n");
  Wire.begin();
  delay(750);
  Wire1.begin();
  delay(750);
  setupSensors();

  if (erMen){
    chirp(buzzerPin);
    delay(500);    
    chirp(buzzerPin);
    delay(500);
    chirp(buzzerPin);
  }

  startTimeUK=millis();
}

void loop() {
  
  rec.time.setdt();
  rec.state = stateCheck();

  recSensors();
  

  switch(rec.state){
    case 0:
      below_target();
      blink();
      break;
    case 1:
      target_alt();
    case 2:
      descent();
    case 3:
      standby();
      blink();
      break;
    default:
      nError = -1;
      blink();
      break;
  }

  output();

}

void below_target(){

}

void target_alt(){
  unsigned long currTime=millis();


  if(startTimeUK+25<=currTime) {
    TheUK.update(10);
    startTimeUK=millis();
  }
  //data collection goes here
}

void descent(){

}

void standby(){
  delay(standby_delay);
}

void fetch(){
  if(erGay)  {gayDar.prefetchData();}
  if(erGuy)  {guy.prefetchData();}
  if(erDude) {dude.performReading();}
}

void recSensors(){
  fetch();
  if(erMen){
    rec.GPS.setX(hotMenInYourArea.getLongitude());
    rec.GPS.setY(hotMenInYourArea.getLatitude());
    rec.GPS.setZ(hotMenInYourArea.getAltitude());
    rec.time.setUTC(&hotMenInYourArea);
  }

  if(erGay){
    rec.Gyro.setX(gayDar.getGyroX());
    rec.Gyro.setY(gayDar.getGyroY());
    rec.Gyro.setZ(gayDar.getGyroZ());

    rec.Acc.setX(gayDar.getAccelerationX());
    rec.Acc.setY(gayDar.getAccelerationY());
    rec.Acc.setZ(gayDar.getAccelerationZ());
  }

  if(erGuy){
    rec.tempI = guy.getTemperature();
    rec.humidity = guy.getHumidity();
  }

  if(erDude){
    rec.tempE = dude.readTemperature();
    rec.pressure = dude.readPressure();
  }
}

void output(){
  Serial1.print(rec.outCSV()); // replace -1 w/ current time from rework clock function
  Serial.println(rec.outCSV()); // replace -1 w/ current time from rework clock function
  Serial.println();
}

void blink(){
  static int t;
  t+=rec.time.dt;

if(LED1.getState()){
  if(t>led_duration){
    LED1.off();
    LED2.off();
    t = 0;
  } 
}else if(t>led_delay){
    LED1.on();
    LED2.on(

    );
    t = 0;
  }
}

void chirp(int pin){
  for(int i = 0; i < 400; i++){
        digitalWrite(pin,HIGH);
        delayMicroseconds(i);
        digitalWrite(pin,LOW);
        delayMicroseconds(i);
    } 
    for(int i = 400; i > 0; i--){
        digitalWrite(pin,HIGH);
        delayMicroseconds(i);
        digitalWrite(pin,LOW);
        delayMicroseconds(i);
    } 
}

void testSolenoids() {
    delay(1000);

    digitalWrite(solenoid_pin1, HIGH);
    delay(100);
    digitalWrite(solenoid_pin1, LOW);

    digitalWrite(solenoid_pin2, HIGH);
    delay(100);
    digitalWrite(solenoid_pin2, LOW);
}

void testTargetValueInfo() {
    //Testing Target Value
    Serial.print("Target value: ");
    Serial.println(TheUK.findNewTarget());

    Serial.println("\n Dirrection: ");
    Serial.println(TheUK.testRun());

    Serial.println("\n Hour: ");
    Serial.println(hotMenInYourArea.getHour());

    Serial.println("\n Minute: ");
    Serial.println(hotMenInYourArea.getMinute());
}

void solenoidsTranslate(int instruction) {    
    //Running the test to see if the payload spins correctly
    // int instruction = update();//stab.testRun();

    if (instruction==CLOCKWISE) {//turn on 'right' solenoid???
        digitalWrite(solenoid_pin1,LOW);
        digitalWrite(solenoid_pin2,HIGH);
        Serial.println("clockwise");
    }
    else if (instruction==COUNTERCLOCKWISE) {//turn on 'left' solenoid???
        digitalWrite(solenoid_pin2, LOW);
        digitalWrite(solenoid_pin1, HIGH);
        Serial.println("counter");
    }
    else if (instruction==2) {//do nothing. Even the solenoids aren't being turned off        
        Serial.println("nothing");
    }
    else {//instruction==CLOCKFOOL -> turn everything off
        digitalWrite(solenoid_pin1, LOW);
        digitalWrite(solenoid_pin2, LOW);
        Serial.println("fool");
    }

    Serial.println(TheUK.getAngularPos());

    //delay(50);//for testing, we will use delay. For the flight code, don't
}

int stateCheck(){
  static unsigned long int dur[4];
  int dih = rec.getDh();
  int h = rec.getH();
  // checks values based on state: can move forward only one state at a time 
  switch(rec.state){
    case 0: // ascent to target alt
      if(h >= target_altitude){
        dur[0] += rec.time.dt;
      }else{dur[0]=0; dur[1]=0; dur[2] = 0;}

    case 1: // target alt to descent
      if(dih<0){
        dur[1]+= rec.time.dt;
      }else if(h < target_altitude){  // revert chack to state ascent
        dur[1] = 0;
        dur[0] += rec.time.dt;
      }else{dur[0]=0; dur[1]=0; dur[2] = 0;}

    case 2: // descent to standby
      if(dih > standby_thresh || dih < -standby_thresh){
        dur[2] += rec.time.dt;
      }else if(dih<0){ // revert check to descent
        dur[1] += rec.time.dt;
        if(dur[1] > rec.time.dt*standby_exit_mod) // because negative dh could be higher than expected while in standby it must be continous for longer to reset progress towards standby
          dur[2] = 0;
      }else{dur[0]=0; dur[1]=0; dur[2] = 0;}

    case 3: // standby operates seperate from others and only goes to target altitude
      if(h > target_altitude){
        dur[3] += rec.time.dt;
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
  return -1;
}

void setupSensors(){
  // M9N
  delay(500);
  for(int i = 0; (i< attempt_num) && !(hotMenInYourArea.begin()); i++){
    Serial.println(" M9N not found     :(");
    if(i==attempt_num){
      erMen = false;
      Serial.println(" M9N failed to initialize.    IE1");
      Serial1.print("M9N-1, ");
    }
    delay(attempt_delay);
  }
  if(erMen){
  hotMenInYourArea.setI2COutput(COM_TYPE_UBX);
  hotMenInYourArea.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT);
  }
  
Serial.println("M9N checked.");
  delay(500);
  // BNO055 bad
  for(int i = 0; (i<= attempt_num) && (gayDar.init() == BNO_ERROR); i++){
    Serial.println(" BNO055 not found   >:(");
    if(i==attempt_num){
      erGay = false;
      Serial.println(" BNO055 failed to initialize.  IE2");
      Serial1.print("BNO055-1, ");
    }
    delay(attempt_delay);
  }
  delay(500);

  //BME280 (evil dastardly bad guy)
  Serial.println("BNO checked.");
  for(int i = 0; (i<= attempt_num) && (guy.init() == BME_ERROR); i++){
    Serial.println(" BME280 not found  )=:");
    delay(100);
    Serial.println(guy.init() == BME_ERROR);
    if(i==attempt_num){
      erGuy = false;
      Serial.println(" BME280 failed to initialize. IE3");
      Serial1.print("BME280-1, ");
    }
    delay(attempt_delay);
  }

  Serial.println("BME checked.");
  delay(500);
  //BMP3 good boy
  for(int i = 0; (i<= attempt_num) && !(dude.begin_I2C(BMP3XX_DEFAULT_ADDRESS,&Wire1)); i++){
    // Serial.print("the bmp is begingin? - ");
    //Serial.println(dude.begin_I2C(BMP3XX_DEFAULT_ADDRESS,&Wire1));
    // Serial.print("the attempt num is... ");
    // Serial.println(i);
    // Serial.println(" BMP3 not found    :()");
    if(i==attempt_num){
      erDude = false;
      Serial.println(" BMP3 failed to initialize.   IE4");
      Serial1.print("BMP3-1, ");
    }
    delay(attempt_delay);
  }
  if(erDude){
  dude.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  dude.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  dude.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  dude.setOutputDataRate(BMP3_ODR_50_HZ);
  }
/*
  // INA260 also evil  bad never ever ever again
  power = Adafruit_INA260();
  for(int i = 0; (i<= attempt_num) || !power.begin(); i++){
    Serial.println(" INA260 not found    :()");
    if(i==attempt_num){
      erDude = false;
      Serial.println(" INA260 failed to initialize. IE5");
      Serial1.print("INA260-1, ");
    }
    delay(attempt_delay);
  }
*/
Serial.println("d");
  Serial.println(" Sensors Initlialized: .");
  if(erMen){Serial.println("\n  M9N");}
  if(erGay){Serial.println("\n  BNO055");}
  if(erGuy){Serial.println("\n  BME280");}
  if(erDude){Serial.println("\n  BMP3");}
  if(!(erMen|| erGay|| erGuy|| erDude)){Serial.println("\n  None");}
  
 
}
