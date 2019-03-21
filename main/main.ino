#include <SD.h>
#include <SD_t3.h> // Required extension for the Teensy 3.2
#include <SPI.h>
#include "util.h" // Various utilities for SD Card usage, debugging, etc...
#include "sensors.h" // Functions relating to the usage and init of sensors


#define GPS_SERIAL Serial2



// Files.
char filename[13] = "LOGGER00.CSV"; 
File logger;

 



void setup() {
    Serial.begin(9600);
    debug("Serial Test...");

    GPS_SERIAL.begin(9600); // GPS Hardware Serial.

    pinMode(SD_CS, OUTPUT);
    pinMode(BME_CS, OUTPUT);

    switchSPI(SD_CS, BME_CS);
    sd_init(SD_CS);

    switchSPI(BME_CS, SD_CS);
    bme_init(BME_CS);
    switchSPI(SD_CS, BME_CS);

    ds_init();
}

void loop() {
  // put your main code here, to run repeatedly:

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
                  debugBlink(13); // Blinkenlights are for emergencies only.g               
              }
            }
            
            
            filename[6] = i / 10 + '0'; // Sets the first number to be the 'Tens' digit of i.
            filename[7] = i % 10 + '0'; // Sets the second number to be the 'Ones' digit of i.

            

            debug(filename);
        }
    }
}
