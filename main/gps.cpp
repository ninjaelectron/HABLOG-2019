#include <Arduino.h>
#include <Adafruit_GPS.h>
#include "gps.h"
#include "util.h"
#include <TimeLib.h> // For Timekeeping.

HardwareSerial gpsSerial = Serial1;
Adafruit_GPS gps(&gpsSerial);

const boolean gps_DEBUG = true; // Debug toggle.

void gps_init() {
    gps.begin(9600); // Begin Communication with GPS Module.
    gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // Output values required for usage.
    delay(500);
    gps.sendCommand(PMTK_SET_NMEA_UPDATE_1_HERTZ); // Update values 5 seconds.
}

boolean gps_readWrapper() {
    char c = gps.read();

    if (gps_DEBUG) Serial.print(c);

    if (gps.newNMEAreceived()) { // Got from gps_readWrapper().
        if (!gps.parse(gps.lastNMEA())) {
            return false; // Cancel data upload if GPS Fails. Probably will cause problems.    
        }
        if (gps.fix) {
            setTime(gps.hour, gps.minute, gps.seconds, gps.day, gps.month, gps.year); // Sync time from GPS over to Teensy internal RTC.
        }
        return true; // Good to acquire data.
    }
    return false; // No data to acquire yet.
}

int gps_getSeconds() { // For validation purposes.
    return gps.seconds;
}

char* gps_getLatLong() { // Get current location (in a Google Maps-compliant format).
    float latitude = gps.latitudeDegrees;
    float longitude = gps.longitudeDegrees;
    char outputLat[11] = "";
    char outputLong[11] = "";
    static char finalOutput[23] = "";

    dtostrf(latitude,0,4,outputLat); // dtostrf arg2 is minimum characters, not expected
    dtostrf(longitude,0,4,outputLong);
    
    sprintf(finalOutput, "%s,%s,", outputLat, outputLong);

    return finalOutput;

    free(outputLat); // Clear memory associated with the variable.
    free(outputLong);
}

char* gps_getTime() { // Get current UTC Time.
    static char out[9] = "";

    sprintf(out, "%02u:%02u:%02u,", gps.hour,gps.minute,gps.seconds);

    return out;
}

char* gps_getFlightParameters() { // Get speed, altitude, etc...
    char speedKnots[6] = "";
    char altitudeMeters[9] = "";
    static char out[12] = "";

    dtostrf(gps.speed, 0, 1, speedKnots);
    dtostrf(gps.altitude, 0, 1, altitudeMeters);
    sprintf(out, "%s,%s,", altitudeMeters,speedKnots);

    return out;

    free(speedKnots);
    free(altitudeMeters);
}



char* gps_getMiscData() { // Get various data such as fix quality.
    static char out[6] = "";
    sprintf(out, "%u,%u,", gps.fixquality,gps.satellites);

    return out;
}

boolean gps_getFix() {
  return gps.fix;
}
