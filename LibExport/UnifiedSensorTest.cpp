#include <Adafruit_BME280.h>
#include <Wire.h>
#include <Adafruit_INA260.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//Serial Double Printing
#define BOTH_PRINT(...) { Serial.print(__VA_ARGS__); Serial1.print(__VA_ARGS__); }
#define BOTH_PRINTln(...) { Serial.println(__VA_ARGS__); Serial1.println(__VA_ARGS__); }

//Sensor Statuses
bool BattSenseINA260Status = false;
bool GPSM9NStatus = false;
bool InternalAirSensorBme280Status = false;
bool IMUBno055Status = false;

// Sensor objects
Adafruit_INA260 ina260 = Adafruit_INA260();;
SFE_UBLOX_GNSS myGNSS;
Adafruit_BME280 bme; // use I2C interface
Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();
uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);

// INA260 data structure
struct BattSenseINA260DataStruct {
  float Current;
  float BusVoltage;
  float Power;
};

// GPS data structure
struct GPSM9NDataStruct {
  long latitude;
  long longitude;
  long altitude;
  byte SIV;
};

//Internal AirSensor(INA280) data structure
struct InternalAirSensorBme280Struct {
  //*C
  float temperature;
  //%
  float relative_humidity;
  //hpa
  float pressure;

};


//IMU(BNO055) data structure
struct IMUBno055Struct {
  double x;
  //%
  double y;
  //hpa
  double z;

};


// Function declarations
bool BattSenseINA260Setup();
bool GPSM9NSetup();
bool InternalAirSensorBme280Setup();
bool IMUBNO055Setup();


BattSenseINA260DataStruct BattSenseINA260GetData();
GPSM9NDataStruct GPSM9NGetData();
InternalAirSensorBme280Struct InternalAirSensorBme280GetData();
IMUBno055Struct IMUBno055GetData();

// Initialize INA260
bool BattSenseINA260Setup() {
  if (!ina260.begin()) {
    BOTH_PRINTln("Couldn't find INA260 chip");
    return false;
  }

  BOTH_PRINTln("Found INA260 chip");
  return true;
}


// Initialize GPS
bool GPSM9NSetup() {
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


bool InternalAirSensorBme280Setup() {
  if (!bme.begin()) {
    BOTH_PRINTln(F("Could not find a valid BME280 sensor, check wiring!"));
    return false;
  }
  // bme_temp->printSensorDetails();
  // bme_pressure->printSensorDetails();
  // bme_humidity->printSensorDetails();
  return true;
}


bool IMUBNO055Setup() {
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

void setup() {
  delay(500);
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(500);

  BOTH_PRINTln("Cassiopeia Electrical Unified Test");

  // Initialize I2C before initializing either sensor
  //Wire.begin();


  BattSenseINA260Status = BattSenseINA260Setup();
  BOTH_PRINT("\n");
  BOTH_PRINTln("INASETUP:");
  BOTH_PRINTln(String(BattSenseINA260Setup()));
  BOTH_PRINT("\n");

  GPSM9NStatus = GPSM9NSetup();
  BOTH_PRINT("\n");
  BOTH_PRINTln("GPSSETUP:");
  BOTH_PRINTln(String(GPSM9NSetup()));
  BOTH_PRINT("\n");

  InternalAirSensorBme280Status = InternalAirSensorBme280Setup();
  BOTH_PRINT("\n");
  BOTH_PRINTln("InternalAirSensorSETUP:");
  BOTH_PRINTln(String(InternalAirSensorBme280Setup()));
  BOTH_PRINT("\n");

  IMUBno055Status = IMUBNO055Setup();
  BOTH_PRINT("\n");
  BOTH_PRINTln("IMUSETUP:");
  BOTH_PRINTln(String(IMUBNO055Setup()));
  BOTH_PRINT("\n");
}


// Read and return INA260 data
BattSenseINA260DataStruct BattSenseINA260GetData() {
  BattSenseINA260DataStruct readings;

  readings.Current = ina260.readCurrent();
  readings.BusVoltage = ina260.readBusVoltage();
  readings.Power = ina260.readPower();

  return readings;
}


// Read and return GPS data
GPSM9NDataStruct GPSM9NGetData() {
  GPSM9NDataStruct readings;

  readings.latitude = myGNSS.getLatitude();
  readings.longitude = myGNSS.getLongitude();
  readings.altitude = myGNSS.getAltitude();
  readings.SIV = myGNSS.getSIV();

  return readings;
}

//Airsensor get data
InternalAirSensorBme280Struct InternalAirSensorBme280GetData() {
  InternalAirSensorBme280Struct readings;
  sensors_event_t temp_event, pressure_event, humidity_event;
  bme_temp->getEvent(&temp_event);
  bme_pressure->getEvent(&pressure_event);
  bme_humidity->getEvent(&humidity_event);
  
  readings.temperature = temp_event.temperature;

  readings.relative_humidity = humidity_event.relative_humidity;

  readings.pressure = pressure_event.pressure;
  return readings;
}

//IMU get data
IMUBno055Struct IMUBno055GetData() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  IMUBno055Struct readings;
  readings.x = euler.x();
  readings.y = euler.y();
  readings.z = euler.z();
  return readings;
}

// Arduino loop
void loop() {

  BOTH_PRINTln("_______________________________________________________________________");


  // Read INA260
  if (BattSenseINA260Status) {
  BattSenseINA260DataStruct battery = BattSenseINA260GetData();
  BOTH_PRINT("\n");
  BOTH_PRINT("INADATA:");
  BOTH_PRINT("Current=");
  BOTH_PRINT(battery.Current);
  BOTH_PRINT(", BusVoltage=");
  BOTH_PRINT(battery.BusVoltage);
  BOTH_PRINT(", Power=");
  BOTH_PRINTln(battery.Power);
  BOTH_PRINT("\n");
  }

  // Read GPS
  if (GPSM9NStatus){
  GPSM9NDataStruct gps = GPSM9NGetData();
  BOTH_PRINT("\n");
  BOTH_PRINT("GPSDATA:");
  BOTH_PRINT("Latitude=");
  BOTH_PRINT(gps.latitude);
  BOTH_PRINT(", Longitude=");
  BOTH_PRINT(gps.longitude);
  BOTH_PRINT(", Altitude=");
  BOTH_PRINT(gps.altitude);
  BOTH_PRINT(", SIV=");
  BOTH_PRINTln(float(gps.SIV));
  BOTH_PRINT("\n");
  }
  //ReadBME280
  if (InternalAirSensorBme280Status) {
  InternalAirSensorBme280Struct IAS = InternalAirSensorBme280GetData();
  BOTH_PRINT("\n");
  BOTH_PRINT(F("Temperature = "));
  BOTH_PRINT(IAS.temperature);
  BOTH_PRINTln(" *C");

  BOTH_PRINT(F("Humidity = "));
  BOTH_PRINT(IAS.relative_humidity);
  BOTH_PRINTln(" %");

  BOTH_PRINT(F("Pressure = "));
  BOTH_PRINT(IAS.pressure);
  BOTH_PRINTln(" hPa");
  BOTH_PRINT("\n");
  }

  //Read IMU
  if (IMUBno055Status) {
  IMUBno055Struct IMU = IMUBno055GetData();
  BOTH_PRINT("\n");
  BOTH_PRINT("X: ");
  BOTH_PRINT(IMU.x);
  BOTH_PRINT(" Y: ");
  BOTH_PRINT(IMU.y);
  BOTH_PRINT(" Z: ");
  BOTH_PRINT(IMU.z);
  BOTH_PRINT("\t\t");
  BOTH_PRINT("\n");
  }
  delay(1000);
}