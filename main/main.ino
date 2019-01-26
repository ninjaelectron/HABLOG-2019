#include <SD_t3.h>
#include <SPI.h>

// Declare any constant pinouts here.
const int BUILTIN_LED = 13;
const int SPI_MISO = 12;
const int SPI_MOSI = 11;

// SPI Chip-Select Pins.
const int SD_CS = 10;

// Files.
char filename[12]; 
File logger;

void setup() {
    Serial.begin(9600); // Enable the main USB Serial object.
    Serial.println("HABLOG Test");
  
    if (SD.begin(SD_CS)) { // Enable SD Card Reader, with a Chip-Select on pin 4. Change this pin to allow for communication with other SPI devices.
        // Error-handling
        Serial.println("SD Error.");
    }

    filename[] = "LOGGER00.CSV"

    for (uint8_t i = 0; i < 100; i++) {
        if (!SD.exists(filename)) {
            logger = File.open(filename);  
        } else {
            filename[6] = i / 10 + '0';
            filename[7] = i % 10 + '0';

            Serial.println(filename);
        }
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}
