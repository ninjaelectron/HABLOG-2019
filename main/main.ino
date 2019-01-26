#include <SD.h>
#include <SD_t3.h> // Required extension for the Teensy 3.2
#include <SPI.h>

// Declare any constant pinouts here.
const int BUILTIN_LED = 13;
const int SPI_MISO = 12;
const int SPI_MOSI = 11;

// SPI Chip-Select Pins.
const int SD_CS = 10;
const int BME_CS = 9;

// Files.
char filename[13] = "LOGGER00.CSV"; 
File logger;

void debug(char c[]) { // Prints to serial console. Easily disabled.
    Serial.println(c);
}

void switchSPI(int enabled, int disabled) { // Switch which SPI Device is being used.
  digitalWrite(enabled, HIGH);
  digitalWrite(disabled, HIGH);
  
  digitalWrite(enabled, LOW);
}

void setup() {
    Serial.begin(9600);
    debug("Serial Test...");

    pinMode(SD_CS, OUTPUT);
    pinMode(BME_CS, OUTPUT);

    switchSPI(SD_CS, BME_CS);

    if(!SD.begin(SD_CS)) { // Check if SD Card can be found.
        debug("Error: SD Card not found.");
    } else {
        debug("SD Card found!");
    }

    for (uint8_t i = 0; i < 100; i++) { // Iterates through 100 possible file names.
        if (!SD.exists(filename)) {
            logger = SD.open(filename, FILE_WRITE);  
        } else {
            filename[6] = i / 10 + '0'; // Sets the first number to be the 'Tens' digit of i.
            filename[7] = i % 10 + '0'; // Sets the second number to be the 'Ones' digit of i.

            debug(filename);
        }
    }

}

void loop() {
  // put your main code here, to run repeatedly:

}
