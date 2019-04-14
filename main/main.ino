#include <SD.h>
#include <SD_t3.h> // Required extension for the Teensy 3.2
#include <SPI.h>
#include "util.h" // Various utilities for SD Card usage, debugging, etc...
#include "sensors.h" // Functions relating to the usage and init of sensors
#include "gps.h"

// Precompiler Definitions.
#define GPS_SERIAL Serial1

char dataBuffer[64];
int secondCheck = 99; // Validation via seconds on GPS Clock.

// Files.
char filename[13] = "LOGGER00.CSV"; 
File logger;

void setup() {
    Serial.begin(9600);
    debug("Serial Test...");

    GPS_SERIAL.begin(9600); // GPS Hardware Serial.

    pinMode(SD_CS, OUTPUT);
    pinMode(BME_CS, OUTPUT);

    gps_init();

    switchSPI(SD_CS); // Switch SPI Devices to SD. (Bring SD_CS LOW, BME_CS HIGH).
    sd_init(SD_CS);

    bme_init();

    // ds_init();
    uv_init();
    
    // Send in short bursts to not overwhelm the SD Board.
    sd_send("Garden City Gopherspace HABLOG\n");
    sd_send("Time,Latitude,Longitude,");
    sd_send("Altitude (m),");
    sd_send("Internal Temperature (C),");
    sd_send("Internal Pressure (kPa),Humidity (%),");
    sd_send("Fix Quality (Debug),Satellites,UV Data (Raw)\n");
    logger.close();
}

void loop() {
    
    if (gps_readWrapper() && (secondCheck != gps_getSeconds())) { // Tests for duplicate logging periods.
        // Continue with data acquisition.
      
        // Dataformat: GPSTime,GPSLatLong,GPSData
        //sprintf(dataBuffer, "%s%s%s", gps_getTime(),gps_getLatLong(),gps_getMiscData());
        
        switchSPI(SD_CS);
        logger = SD.open(filename, FILE_WRITE);
        sd_send(gps_getTime());
        sd_send(gps_getLatLong());
        sd_send(gps_getFlightParameters());
        sd_send(bme_packageData());
        sd_send(gps_getMiscData());
        sd_send(uv_packageData());
        sd_send("\n");
        logger.close();
        //Serial.println(gps_getLatLong());

        secondCheck = gps_getSeconds();
    }
}

void sd_init(int cs) {
  
    if(!SD.begin(cs)) { // Check if SD Card can be found.
        debug("Error: SD Card not found.");
    } else {
        debug("SD Card found!");
    }

    for (uint8_t i = 0; i < 100; i++) { // Iterates through 100 possible file names.
        if (!SD.exists(filename)) {
            logger = SD.open(filename, FILE_WRITE); // Open the available file.
            
            debug("Using filename: ");
            debug(filename);
            
            break;  
        } else {
            if (filename == "LOGGER99.CSV") {
              debug("Error: Not enough space on SD Card!");

              while (true) {
                  debugBlink(13); // Blinkenlights are for emergencies only.               
              }
            }
            
            
            filename[6] = i / 10 + '0'; // Sets the first number to be the 'Tens' digit of i.
            filename[7] = i % 10 + '0'; // Sets the second number to be the 'Ones' digit of i.

            

            debug(filename);
        }
    }
}

void sd_send(char* c) { // Send data to SD Card (Hopefully Safely) 
    Serial.print(c);   
    logger.print(c);
    logger.flush();
}
