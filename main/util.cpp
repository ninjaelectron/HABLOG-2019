#include "util.h"
#include <arduino.h>
#include <SPI.h>

int currentSPI = 0; // Current SPI Bus. Starts blank.
int currentSCK = SD_SCK;

void switchSPI(int targetCS, int targetSCK) { // Switch which SPI Device is being used.
    if (currentSPI != targetCS) {
        for (uint32_t i = 0; i < sizeof(CS_PINS); i++) {
            digitalWrite(i, HIGH); // Bring all CS Lines HIGH (disabled).
        }
    }
        SPI.setSCK(targetSCK);
    
        digitalWrite(targetCS, LOW); // Bring target CS Line LOW.

        currentSCK = targetSCK;
        currentSPI = targetCS;
}

void debugBlink(int pin) {
    delay(100);
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
}

void debug(char c[]) { // Prints to serial console. Easily disabled.
    Serial.println(c);
}

bool checkArmed() {
    return digitalRead(ARM_PIN);
}
