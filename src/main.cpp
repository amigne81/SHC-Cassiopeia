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
Data rec = Data();
StabAlg TheUK = StabAlg(hotMenInYourArea, gayDar);
LED LEDs(2);

int temp;

int mostRecentYear = 0;
int mostRecentMonth = 0;
int mostRecentDay = 0;
int mostRecentHour = 0;
int mostRecentMinute = 0;
int mostRecentSecond = 0;
int mostRecentSIV = 0;
double mostRecentLongitude = 0.0;
double mostRecentLatitude = 0.0;
double mostRecentAltitude = 0.0;

// global variable intialization
const int solenoid_pin1 = 3;
const int solenoid_pin2 = 4;
const int buzzerPin = 5;

const int attempt_num = 100;        // number of attempts made before giving up on sensor
const int target_altitude = 20000;
const int standby_thresh = 1;
const int standby_exit_mod = 8; 
int LED_count;
int nError = 0;
bool erMen = true, erGay = true, erGuy = true, erDude = true, erPower = true;

// time duration requiredments to switch states in milliseconds: to target alt, to descent, to standby
const unsigned long int tReq[3] = {20000,30000,60000};
const int emergency_standby_exit= 5000; // time to exit if in target alt while in standby state (milliseconds)
const int attempt_delay = 150; // delay between attempts of sensor initialization
const int led_delay = 460;    // delay is between flashes, duration is the length of flashes
const int led_duration = 40;
const int standby_delay = 3000;
int i = 0;


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
void Stabtest();
void testSolenoids();
void testTargetValueInfo();
void testOrientation();
void chirp(int);
void recMen();
void outMen();
void gayWreck();
void outCloset();
void recGuy();
void outGuy();
void recDude();
void outDude();
Error init();

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

  testSolenoids();
  chirp(5);
  chirp(5);

  startTimeUK=millis();
}

void loop() {
  if(i==4){
    recSensors();
    i=0;
  }
  i++;

  //sets dt for the entire loop, to keep the timing consistent with all functions
  rec.time.setdt();
  
  //===================================================================================================================================================
  //FRR TESTING
  rec.state = 1;
  //====================================================================================================================================================
  
  //UNCOMMENT AFTER TESTING
  //rec.state = stateCheck();

  //takes in the state, calls the function for that state
  //ex. rec.state = 1 -> stabilize
  switch(rec.state){
    case 0:
      below_target();
      break;
    case 1:
      target_alt();
      break;
    case 2:
      descent();
      break;
    case 3:
      standby();
      break;
    default:
      nError = -1;
      break;
  }

  if(rec.state!=3){
    blink();
  }

  Serial.print("state: ");
  Serial.println(rec.state);
  
  output();
  // delay(5000) // for testing
}

//when we are below target do nothing
void below_target(){

}

//when we are at target alt run stabilization alg
void target_alt(){
  unsigned long currTime=millis();

  if(startTimeUK+25<=currTime) {
    TheUK.update(10);
    startTimeUK=millis();
  }
  //data collection goes here
}

//in descent do nothing
void descent(){

}

//in standby delay to conserve battery
void standby(){
  delay(standby_delay);
}

//get the data from the sensors
void fetch(){
  if(erMen){hotMenInYourArea.checkUblox();
  hotMenInYourArea.checkCallbacks();}
  if(erGay)  {gayDar.prefetchData();}
  if(erGuy)  {guy.prefetchData();}
  if(erDude) {dude.performReading();}
}

//record gps data
void recMen(){
  // Serial.println("M9N");
  // Serial.println(millis());
  rec.GPS.setX(mostRecentLongitude);
  // Serial.println(millis());
  rec.GPS.setY(mostRecentLatitude);
  // Serial.println(millis());
  rec.GPS.setZ(mostRecentAltitude);
  
}

//set UTC time to most recent time from satellite
void setUTC(){
  Serial.println(mostRecentHour);
  Serial.println(", ");//+ 
	Serial.println(mostRecentMinute); 		
  Serial.println(", ");
	Serial.println(mostRecentSecond); 		
  Serial.println(", ");
	Serial.println(mostRecentMonth); 			
  Serial.println(", ");
	Serial.println(mostRecentDay);			
  Serial.println(", ");
	Serial.println(mostRecentYear);	

  Serial1.println(mostRecentHour);
  Serial1.println(", ");//+ 
	Serial1.println(mostRecentMinute); 		
  Serial1.println(", ");
	Serial1.println(mostRecentSecond); 		
  Serial1.println(", ");
	Serial1.println(mostRecentMonth); 			
  Serial1.println(", ");
	Serial1.println(mostRecentDay);			
  Serial1.println(", ");
	Serial1.println(mostRecentYear);	
}

//record bno data
void gayWreck(){
  // Serial.println("BNO:");
  // Serial.println(millis());
  rec.Gyro.setX(gayDar.getGyroX());
  // Serial.println(millis());
  rec.Gyro.setY(gayDar.getGyroY());
  // Serial.println(millis());
  rec.Gyro.setZ(gayDar.getGyroZ());
  // Serial.println(millis());
  rec.Acc.setX(gayDar.getAccelerationX());
  // Serial.println(millis());
  rec.Acc.setY(gayDar.getAccelerationY());
  // Serial.println(millis());
  rec.Acc.setZ(gayDar.getAccelerationZ());
  // Serial.println(millis());
}

//record bme data
void recGuy(){
  // Serial.println("BME: ");
  // Serial.println(millis());
  rec.tempI = guy.getTemperature();
  // Serial.println(millis());
  rec.humidity = guy.getHumidity();
  // Serial.println(millis());
}

//record bmp data
void recDude(){
  // Serial.println("BMP");
  // Serial.println(millis());
  rec.tempE = dude.readTemperature();
  // Serial.println(millis());
  rec.pressure = dude.readPressure();
  // Serial.println(millis());
}

//record all sensors
void recSensors(){
  fetch();

  if(erMen){recMen();}
  if(erGay){gayWreck();}
  if(erGuy){recGuy();}
  if(erDude){recDude();}
}

//output to serial
void output(){
  Serial1.print(rec.outCSV()); // replace -1 w/ current time from rework clock function
  Serial.println(rec.outCSV()); // replace -1 w/ current time from rework clock function
  setUTC();
  Serial1.print(hotMenInYourArea.getSIV());
}

//blink LEDs at 1 hz
void blink(){
  LED_count+=rec.time.dt;
  // Serial.print("LED t: ");
  // Serial.println(LED_count);
if(LEDs.getState()){
  if(LED_count>led_duration){
    LEDs.off();
    LED_count = 0;
  } 
}else if(LED_count>led_delay){
    LEDs.on();
    LED_count = 0;
  }
}

//chirps buzzer once
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

//test solenoids
void testSolenoids() {
    delay(1000);

    digitalWrite(solenoid_pin1, HIGH);
    delay(100);
    digitalWrite(solenoid_pin1, LOW);

    digitalWrite(solenoid_pin2, HIGH);
    delay(100);
    digitalWrite(solenoid_pin2, LOW);
}

//uses printlns to test target value
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

int lastDur = 0;

int stateCheck(){
  static unsigned long int dur[4];
  int dih = rec.getDh();
  int h = rec.getH();
  long t = millis();


  // testing -------------------------------------- this never went into landing stage bc it was continuously decrasing
//   long h;
//   long dih;
//   h = (-(77/56)*(t/1000)*((t/1000)-300));
//   //dih = (-77/5)*(2*t-300);


//   Serial.print("h:     ");
//   Serial.println(h);
//   Serial.print("t:     ");
//   Serial.println(t);
//   Serial.println("dih: ");
//  Serial.println(dih);
  // -----------------------------------------------------

  

  // checks values based on state: can move forward only one state at a time
  switch(rec.state){
    case 0: // ascent to target alt
    if(h > target_altitude){
      if((t-lastDur) > 30000){
        lastDur = t;
        rec.state = 1;
        return 1;
      }
    }
    else{
      lastDur = t;
    }
      break;


    case 1: // target alt to descent
    if(dih < 0){
      if((t-lastDur) > 30000){
        lastDur = t;
        // return 2;
        rec.state = 2;
        return 2;
      }
    }
    else{
      lastDur = t;
    }
    break;


    case 2: // descent to standby
      if(dih <= 1 && dih >= -1){
        if((t-lastDur) > 100000){
          lastDur = t;
          rec.state = 3;
          return 3;
        }
      }
      else{
        lastDur = t;
      }
      break;


    case 3: // standby operates seperate from others and only goes to target altitude
      if(dih <= 1 && dih >= -1){
        if((t-lastDur) > 100000){
          lastDur = t;
          // return 3;
          rec.state = 0;
          return 0;
        }
      }
      else{
        lastDur = t;
      }
      break;
  }

  temp = h;
  return rec.state;
}

//initializes sensors
void setupSensors(){
  // M9N
  LEDs.on();
  delay(500);
  for(int i = 0; (i<= attempt_num) && (init() == M9N_ERROR); i++){
    Serial.println(" M9N not found     :(");
    if(i==attempt_num){
      erMen = false;
      Serial.println(" M9N failed to initialize.    IE1");
      Serial1.print("M9N-1, ");
    }
    delay(attempt_delay);
  }
  if(erMen){
  chirp(5);
  hotMenInYourArea.setI2COutput(COM_TYPE_UBX);
  hotMenInYourArea.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT);
  }

  delay(1500);
  LEDs.on();
  delay(500);
  LEDs.off(); 

Serial.println("M9N checked.");
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

  if(erGay){
    chirp(5);
  }

  delay(1500);
  LEDs.on();
  delay(500);
  LEDs.off();

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

  if(erGuy){
    chirp(5);
  }


  delay(1500);
  LEDs.on();
  delay(500);
  LEDs.off();

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
    chirp(5);
  }
  
  delay(1500);
  LEDs.on();
  delay(500);
  LEDs.off();

  Serial.println(" Sensors Initlialized: .");
  if(erMen){Serial.println("\n  M9N");}
  if(erGay){Serial.println("\n  BNO055");}
  if(erGuy){Serial.println("\n  BME280");}
  if(erDude){Serial.println("\n  BMP3");}
  if(!(erMen|| erGay|| erGuy|| erDude)){Serial.println("\n  None");}
}

//print bmp
void outDude(){
  Serial.println("tempE: " + String(dude.readTemperature(),5));
  Serial.println("presr: " + String(dude.readPressure(),5));
}

//print bme
void outGuy(){
  Serial.println("tempI: "+ String(guy.getTemperature(),5));
  Serial.println("humid: "+ String(guy.getHumidity()));
}

//print gps
void outMen(){
  Serial.println("Longitude: "+ hotMenInYourArea.getLongitude());
  Serial.println("Latitude: "+ hotMenInYourArea.getLatitude());
  Serial.println("Altitude: "+ hotMenInYourArea.getAltitude());
}

//print bno
void outCloset(){
  Serial.println("orient X: " + String(gayDar.getOrientationX()));
  Serial.println("orient Y: " + String(gayDar.getOrientationY()));
  Serial.println("orient Z: " + String(gayDar.getOrientationZ()));
  
  Serial.println("Gyro X: " + String(gayDar.getGyroX()));
  Serial.println("Gyro Y: " + String(gayDar.getGyroY()));
  Serial.println("Gyro Z: " + String(gayDar.getGyroZ()));

  Serial.println("Acc X: " + String(gayDar.getAccelerationX()));
  Serial.println("Acc Y: " + String(gayDar.getAccelerationY()));
  Serial.println("ACC Z: " + String(gayDar.getAccelerationZ()));
}

//checks for data updates in the gps, if yes, collect the data
void pvtCallback(UBX_NAV_PVT_data_t *ubxDataStruct) {
    mostRecentLatitude = ((double)ubxDataStruct->lat) * pow(10, -7);
    mostRecentLongitude = ((double)ubxDataStruct->lon) * pow(10, -7);
    mostRecentAltitude = ubxDataStruct->height / 1000.0;
      
    mostRecentYear = (int)ubxDataStruct->year;
    mostRecentMonth = (int)ubxDataStruct->month;
    mostRecentDay = (int)ubxDataStruct->day;
    mostRecentHour = (int)ubxDataStruct->hour;
    mostRecentMinute = (int)ubxDataStruct->min;
    mostRecentSecond = (int)ubxDataStruct->sec;
    mostRecentSIV = ubxDataStruct->numSV;
}

//intializes the gps
Error init() {
    if (!hotMenInYourArea.begin()) {
        return M9N_ERROR;
    }
    hotMenInYourArea.setI2COutput(COM_TYPE_UBX);
    hotMenInYourArea.setNavigationFrequency(5);
    hotMenInYourArea.setDynamicModel(DYN_MODEL_AIRBORNE4g);
    //     //return M9N_ERROR;
    // }
    hotMenInYourArea.saveConfiguration();
    hotMenInYourArea.setAutoPVTcallbackPtr(&pvtCallback);
    //}
    // bool sivCheck = config.waitForGPSLock;

    // Make it not block
    // while (sivCheck) {
    //     m9n.checkUblox();
    //     m9n.checkCallbacks();
    //     switch (mostRecentSIV) {
    //         // TODO ERRORS
    //         default:
    //             sivCheck = false;
    //             break;
    //     }
    // }
    return NO_ERROR;
}

//gets data for gps
bool prefetchData() {
    hotMenInYourArea.checkUblox();
    hotMenInYourArea.checkCallbacks();
    // longitude = mostRecentLongitude;
    // latitude = mostRecentLatitude;
    // altitude = mostRecentAltitude;
    // year = mostRecentYear;
    // month = mostRecentMonth;
    // day = mostRecentDay;
    // hour = mostRecentHour;
    // minute = mostRecentMinute;
    // second = mostRecentSecond;
    // SIV = mostRecentSIV;
    return true;
}