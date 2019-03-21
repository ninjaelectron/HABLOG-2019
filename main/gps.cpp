#include <Arduino.h>
#include <Adafruit_GPS.h>
#include "util.h"

const boolean gps_DEBUG = false; // Debug toggle.

Adafruit_GPS gps(&Serial2);

void gps_init() {
    gps.begin(9600); // Begin Communication with GPS Module.
    gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // Output values required for usage.
    gps.sendCommand(PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ); // Update values every second.
}

boolean gps_parseWrapper() { // Returns success/fail of GPS data acquisition.
    if (gps.newNMEAreceived()) { // Got from gps_readWrapper().
        if (!gps.parse(gps.lastNMEA())) {
          return false; // Cancel data upload if GPS Fails. Probably will cause problems.    
        }

        Serial.println(gps.seconds, DEC);

        return true; // Good to acquire data.
    }
    return false; // No data to acquire yet.
}

boolean gps_readWrapper() {
    char c = gps.read();

    if (gps_DEBUG) Serial.print(c);

    return gps_parseWrapper();
}
