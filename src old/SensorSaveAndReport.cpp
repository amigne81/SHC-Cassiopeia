#include "SensorSaveAndReport.h" // Double quotes mean look in the local project folder



#define BOTH_PRINT(...) { Serial.print(__VA_ARGS__); Serial1.print(__VA_ARGS__); }
#define BOTH_PRINTln(...) { Serial.println(__VA_ARGS__); Serial1.println(__VA_ARGS__); }


//Init Functions
// Initialize INA260
bool SSAR::BattSenseINA260Setup() {
  if (!ina260.begin()) {
    BOTH_PRINTln("Couldn't find INA260 chip");
    return false;
  }

  BOTH_PRINTln("Found INA260 chip");
  return true;
}


// Initialize GPS
bool SSAR::GPSM9NSetup() {
  if (!myGNSS.begin()) {
    BOTH_PRINTln(
      "u-blox GNSS not detected at default I2C address. Check wiring."
    );
    return false;
  }

  myGNSS.setI2COutput(COM_TYPE_UBX);
  myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT);

  BOTH_PRINTln("Found u-blox GNSS");
  return true;
}


bool SSAR::InternalAirSensorBme280Setup() {
  if (!bme.begin()) {
    BOTH_PRINTln(F("Could not find a valid BME280 sensor, check wiring!"));
    return false;
  }
  // bme_temp->printSensorDetails();
  // bme_pressure->printSensorDetails();
  // bme_humidity->printSensorDetails();
  return true;
}


bool SSAR::IMUBNO055Setup() {
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    BOTH_PRINT("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    return false;
  }
  int8_t temp = bno.getTemp();
  bno.setExtCrystalUse(true);
  return true;

}

//Initilize BMP388
bool SSAR::ExternalAirSensorBmp388Setup() {
  if (!bmp.begin_I2C(BMP3XX_DEFAULT_ADDRESS,&Wire1)) {   // hardware I2C mode, can pass in address & alt Wire
  //if (! bmp.begin_SPI(BMP_CS)) {  // hardware SPI mode  
  //if (! bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI)) {  // software SPI mode
    BOTH_PRINTln("Could not find a valid BMP3 sensor, check wiring!");
    return false;
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  return true;
}



//Class Init Function
void init() {

}


