#include "util.h"
#include <arduino.h>

int currentSPI = 0; // Current SPI Bus. Starts blank.

void switchSPI(int target) { // Switch which SPI Device is being used.
    if (currentSPI != target) {
        for (uint32_t i = 0; i < sizeof(CS_PINS); i++) {
            digitalWrite(i, HIGH); // Bring all CS Lines HIGH (disabled).
        }
      
        digitalWrite(target, LOW); // Bring target CS Line LOW.

        currentSPI = target;
    }
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
