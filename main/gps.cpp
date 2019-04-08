#include <Arduino.h>
#include <Adafruit_GPS.h>
#include "util.h"

Adafruit_GPS gps(&Serial2);

const boolean gps_DEBUG = false; // Debug toggle.

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

char* gps_getLatLong() { // Get current location (in a Google Maps-compliant format).
    float latitude = gps.latitudeDegrees;
    float longitude = gps.longitudeDegrees;
    char outputLat[11];
    char outputLong[11];
    char finalOutput[22];

    dtostrf(latitude,10,4,outputLat);
    dtostrf(longitude,10,4,outputLong);

    strcat(finalOutput, outputLat);
    strcat(finalOutput, ",");
    strcat(finalOutput, outputLong);

    return finalOutput;

    free(outputLat); // Clear memory associated with the variable.
    free(outputLong);
}

char* gps_getTime() { // Get current UTC Time.
    char out[9] = "";

    sprintf(out, "%u:%u:%u,", gps.hour,gps.minute,gps.seconds);

    return out;
}

char* gps_getFlightParameters() { // Get speed, altitude, etc...
    char speedKnots[6] = "";
    char heading[6] = "";
    char altitudeMeters[9] = "";
    char out[25] = "";

    dtostrf(gps.speed, 6, 1, speedKnots);
    dtostrf(gps.angle, 6, 1, heading);
    dtostrf(gps.altitude, 9, 1, altitudeMeters);
    sprintf(out, "%s,%s,%s,", speedKnots,heading,altitudeMeters);

    return out;

    free(speedKnots);
    free(heading);
    free(altitudeMeters);
}

char* gps_getMiscData() { // Get various data such as fix quality.
    char out[6] = "";
    sprintf(out, "%u,%u,", gps.fixquality,gps.satellites);

    return out;
}
