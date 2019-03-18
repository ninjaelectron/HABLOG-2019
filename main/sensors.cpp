#include <arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include "sensors.h"
#include "util.h"

void bme_init() {
    Adafruit_BME280 pressure(BME_CS);

    if (!pressure.begin()) {
      debug("Pressure Sensor Failed!");
    }
}
