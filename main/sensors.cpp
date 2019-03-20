#include <arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

#include <OneWire.h> // Dependencies for DallasTemperature.h
#include <DallasTemperature.h>

#include "sensors.h"
#include "util.h"

void bme_init(int cs) {
    Adafruit_BME280 pressure(cs);

    if (!pressure.begin()) { // bme.begin() returns true if it succeeds.
      debug("Pressure Sensor Failed!");
    }
}

void ds_init() {
    dsTemp.begin();
}
