// SPI Chip-Select Pins.
const int SD_CS = 10;
const int BME_CS = 9;

const int CS_PINS[2] = {SD_CS, BME_CS}; //  Used for Iterating through with switchSPI(). REMEMBER TO UPDATE IF THE ABOVE CONSTANTS ARE MODIFIED!!!

void switchSPI(int target); // Switch Devices on SPI Bus.

void debugBlink(int pin);
void debug(char c[]); // Debug console messages.

void sd_init(int cs);
void sd_send(char* c);
