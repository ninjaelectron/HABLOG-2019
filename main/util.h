// SPI Chip-Select Pins.
const int SD_CS = 10;
const int BME_CS = 9;

void switchSPI(int enabled, int disabled); // Switch Devices on SPI Bus.

void debugBlink(int pin);
void debug(char c[]); // Debug console messages.

void sd_init();
