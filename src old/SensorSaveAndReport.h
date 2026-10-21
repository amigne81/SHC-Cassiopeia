#ifndef SENSORSAVEANDREPORT_H
#define SENSORSAVEANDREPORT_H

#include <Arduino.h> 
#include <Adafruit_BME280.h>
#include <Wire.h>
#include <Adafruit_INA260.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Adafruit_BMP3XX.h"


//example header class
//SSAR = Sensor Save And Report
class SSAR {
  private:
    //Sensor Objects
    Adafruit_INA260 ina260 = Adafruit_INA260();;

    SFE_UBLOX_GNSS myGNSS;

    Adafruit_BME280 bme; // use I2C interface
    Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
    Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
    Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();

    uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);

    #define BMP_SCK 13
    #define BMP_MISO 12
    #define BMP_MOSI 11
    #define BMP_CS 10
    #define SEALEVELPRESSURE_HPA (1013.25)
    Adafruit_BMP3XX bmp;

    //Data Structures
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

    //External Air Sensor Struct
    struct ExternalAirSensorBmp388Struct {
    //*C
    double temperature;
    //hpa
    double pressure;
    //m
    float readAltitude;

    };
    // Function declarations

    //setups
    bool BattSenseINA260Setup();
    bool GPSM9NSetup();
    bool InternalAirSensorBme280Setup();
    bool IMUBNO055Setup();
    bool ExternalAirSensorBmp388Setup();

    //GetDatas
    BattSenseINA260DataStruct BattSenseINA260GetData();
    GPSM9NDataStruct GPSM9NGetData();
    InternalAirSensorBme280Struct InternalAirSensorBme280GetData();
    IMUBno055Struct IMUBno055GetData();
    ExternalAirSensorBmp388Struct ExternalAirSensorBmp388GetData();

  public:
    bool BattSenseINA260Status = false;
    bool GPSM9NStatus = false;
    bool InternalAirSensorBme280Status = false;
    bool IMUBno055Status = false;
    bool ExternalAirSensorBmp388Status = false;

    // Public methods: Can be called from your main .ino sketch
    void init();

};

#endif
