#include <arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

#include <OneWire.h> // Dependencies for DallasTemperature.h
#include <DallasTemperature.h>

#include "sensors.h"
#include "util.h"

// Declare any constant pinouts here.
const int BUILTIN_LED = 13;
const int SPI_MISO = 12;
const int SPI_MOSI = 11;
const int OneWireBus = 2;

// BME Stuff
Adafruit_BME280 pressure(BME_CS);  

// OneWire stuff
OneWire oneWire(OneWireBus); // Define OneWire Bus
DallasTemperature dsTemp(&oneWire); // Link that bus to the DT Library

// BEGIN BME ROUTINES
void bme_init(int cs) {
    Adafruit_BME280 pressure(cs);

    if (!pressure.begin()) { // bme.begin() returns true if it succeeds.
      debug("Pressure Sensor Failed!");
    }
}
// END BME ROUTINES

// BEGIN DS ROUTINES
void ds_init() {
    dsTemp.begin();
}

int ds_getData() {
  // TODO: Find the specific number of decimal places returned by the DS18B20 device.
}

// END DS ROUTINES
