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
const int ONE_WIRE_BUS = 2;
const int UV_PIN = A1;

// BME Stuff
Adafruit_BME280 bme(BME_CS);  

// OneWire stuff
OneWire oneWire(ONE_WIRE_BUS); // Define OneWire Bus
DallasTemperature dsTemp(&oneWire); // Link that bus to the DT Library

// BEGIN BME ROUTINES
void bme_init() {
    switchSPI(BME_CS);
    if (!bme.begin()) { // bme.begin() returns true if it succeeds.
      Serial.println("Pressure Sensor Failed!");
    } else {
      Serial.println("PGood!");
    }
    switchSPI(SD_CS);
}

char* bme_getPressure() {
    switchSPI(BME_CS);
    static char out[7] = "";
    float pressure = bme.readPressure() / 1000.0;
    //Serial.println(pressure);
    dtostrf(pressure, 0, 1, out);
    return out; // String, Kilopascals. Don't forget the .0 at the end!
    switchSPI(SD_CS);
}

int bme_getHumidity() {
    switchSPI(BME_CS);
    return bme.readHumidity(); // Humidity as integer, percent.
    switchSPI(SD_CS);
}

char* bme_getTemperatureC() {
    switchSPI(BME_CS);
    float temperature = bme.readTemperature();
    static char out[7] = "";

    dtostrf(temperature, 0, 1, out);
    return out; 
    switchSPI(SD_CS);
}

char* bme_packageData() {
    static char out[21] = "";
    
    sprintf(out, "%s,%s,%i,", bme_getTemperatureC(),bme_getPressure(),bme_getHumidity());
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
    static char out[8] = "";
    
    dtostrf(temp, 0, 2, out);
    return out;
}

char* ds_packageData() {
    static char out[9] = "";
    
    sprintf(out, "%s,", ds_getData());
    return out;
}

// END DS ROUTINES

// BEGIN UV ROUTINES
void uv_init() {
    pinMode(UV_PIN, INPUT);
}

int uv_getData() {
    return analogRead(UV_PIN); // Simple Analog read. 0-1023.
}

char* uv_packageData() {
    static char out[6] = "";
    sprintf(out, "%i,", uv_getData());

    return out;
}
// END UV ROUTINES
