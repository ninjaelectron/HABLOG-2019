#include <arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

#include "sensors.h"
#include "util.h"

// Declare any constant pinouts here.
const int BUILTIN_LED = 13;
const int SPI_MISO = 12;
const int SPI_MOSI = 11;
const int UV_PIN = A1;

// BME Stuff
Adafruit_BME280 bme(BME_CS);  

// BEGIN BME ROUTINES
void bme_init() {
    if (!bme.begin()) { // bme.begin() returns true if it succeeds.
      Serial.println("Pressure Sensor Failed!");
    } else {
      Serial.println("PGood!");
    }
}

char* bme_getPressure() {
    static char out[7] = "";
    float pressure = bme.readPressure() / 1000.0;
    //Serial.println(pressure);
    dtostrf(pressure, 0, 1, out);
    return out; // String, Kilopascals. Don't forget the .0 at the end!
}

int bme_getHumidity() {
    return bme.readHumidity(); // Humidity as integer, percent.
}

char* bme_getTemperatureC() {
    float temperature = bme.readTemperature();
    static char out[7] = "";

    dtostrf(temperature, 0, 1, out);
    return out; 
}

char* bme_packageData() {
    switchSPI(BME_CS, BME_SCK);
    static char out[21] = "";
    
    sprintf(out, "%s,%s,%i,", bme_getTemperatureC(),bme_getPressure(),bme_getHumidity());
    return out;
    switchSPI(SD_CS, SD_SCK);
}

// END BME ROUTINES

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
