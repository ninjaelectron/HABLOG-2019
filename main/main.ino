#include <SD.h>
#include <SD_t3.h> // Required extension of SD.h for the Teensy 3.2
#include <SPI.h> // Required for SD and BME Communication.
#include "util.h" // Various utilities for SD Card usage, debugging, etc...
#include "sensors.h" // Functions relating to the usage and init of sensors.
#include "gps.h" // Relating to the GPS Sensor.

#include <TimeLib.h> // Time Library for timekeeping.

// Precompiler Definitions.
#define GPS_SERIAL Serial1 // GPS serial connection.

int secondCheck = 99; // Validation via seconds on GPS Clock.

// Files.
char filename[13] = "LOGGER00.CSV"; 
File logger;

void setup() {

    delay(1000); // Delay for safety purposes.
  
    Serial.begin(9600);
    debug("Serial Test...");

    GPS_SERIAL.begin(9600); // GPS Hardware Serial.

    gps_init();

    pinMode(ARM_PIN, INPUT); // Enable arming switch. High = data flow. Low = prevent data flow.

    pinMode(SD_CS, OUTPUT);
    pinMode(BME_CS, OUTPUT);
    
    switchSPI(SD_CS, SD_SCK); // Switch SPI Devices to SD. (Bring SD_CS LOW, BME_CS HIGH).
    sd_init(SD_CS);

    
    switchSPI(BME_CS, BME_SCK);
    bme_init();
    uv_init();

    switchSPI(SD_CS, SD_SCK);
    
    // Send in short bursts to not overwhelm the SD Board.
    sd_send("Garden City Gopherspace HABLOG\n");
    sd_send("Time,Latitude,Longitude,");
    sd_send("Altitude (m),Speed (kt),");
    sd_send("Temperature (C),");
    sd_send("Pressure (kPa),Humidity (%),");
    sd_send("Fix Quality (Debug),Satellites,UV Data (Raw)\n");
    logger.close();
}

void loop() {
    if (gps_readWrapper() && (secondCheck != second())) { // Tests for duplicate logging periods.

        setTime(gps);
        
        if (checkArmed()) {
            // Continue with data acquisition.
          
            switchSPI(SD_CS, SD_SCK); // Double-check if SD is the current device.
            logger = SD.open(filename, FILE_WRITE);
            sd_send(gps_getTime());
            sd_send(gps_getLatLong());
            sd_send(gps_getFlightParameters());
            sd_send(bme_packageData());
            sd_send(gps_getMiscData());
            sd_send(uv_packageData());
            sd_send("\n");
            logger.close();
        }
        secondCheck = second();
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
    switchSPI(SD_CS, SD_SCK);
    Serial.print(c);   
    logger.print(c);
    logger.flush(); // Fully flush data from cache. Ensures proper writes.
}
