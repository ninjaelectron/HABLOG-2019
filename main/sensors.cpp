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
Adafruit_BME280 bme(BME_CS);  

// OneWire stuff
OneWire oneWire(OneWireBus); // Define OneWire Bus
DallasTemperature dsTemp(&oneWire); // Link that bus to the DT Library

// BEGIN BME ROUTINES
void bme_init(int cs) {
    Adafruit_BME280 bme(cs);

    if (!bme.begin()) { // bme.begin() returns true if it succeeds.
      debug("Pressure Sensor Failed!");
    }
}

int bme_getPressure() {
    return bme.readPressure(); // Integer, Pascals.
}

int bme_getHumidity() {
    return bme.readHumidity(); // Humidity as integer, percent.
}

char* bme_getTemperatureC() {
    float pressure = bme.readTemperature();
    char out[7] = "";

    dtostrf(pressure, 7, 2, out);
    return out; 
}

char* bme_packageData() {
    char out[21] = "";
    
    sprintf(out, "%s,%i,%i,", bme_getTemperatureC(),bme_getPressure(),bme_getHumidity());
    return out;
}

// END BME ROUTINES

// BEGIN DS ROUTINES
void ds_init() {
    dsTemp.begin();
}

char* ds_getData() {
    dsTemp.requestTemperatures(); // Get Temperature from device;
    float temp = dsTemp.getTempCByIndex(0); // Convert to float Degrees C.
    char out[8] = "";
    
    dtostrf(temp, 8, 2, out);
    return out;
}

char* ds_packageData() {
    char out[9] = "";
    
    sprintf(out, "%s,", ds_getData());
    return out;
}

// END DS ROUTINES
