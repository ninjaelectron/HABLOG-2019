// SPI Chip-Select Pins.
const int SD_CS = 10;
const int BME_CS = 9;

// I2C Pins
const int MPU_SCL = 19;
const int MPU_SDA = 18;

const int CS_PINS[3] = {SD_CS, BME_CS};

void switchSPI(int target); // Switch Devices on SPI Bus.

void debugBlink(int pin);
void debug(char c[]); // Debug console messages.

void sd_init(int cs);
void sd_send(char* c);
