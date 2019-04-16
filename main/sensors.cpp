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
