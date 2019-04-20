// SPI Chip-Select Pins.
const int SD_CS = 10;
const int BME_CS = 21;

// SPI Clock Pins.
const int SD_SCK = 13;
const int BME_SCK = 14;

const int CS_PINS[2] = {SD_CS, BME_CS}; //  Used for Iterating through with switchSPI(). REMEMBER TO UPDATE IF THE ABOVE CONSTANTS ARE MODIFIED!!!

const int SCK_PINS[2] = {SD_SCK, BME_SCK};
const int ARM_PIN = 20; // Arm switch.

void switchSPI(int targetCS, int targetSCK); // Switch Devices on SPI Bus.

void debugBlink(int pin);
void debug(char c[]); // Debug console messages.

void sd_init(int cs);
void sd_send(char* c);

bool checkArmed();
