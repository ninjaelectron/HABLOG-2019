#include "util.h"
#include <arduino.h>

void switchSPI(int target) { // Switch which SPI Device is being used.
    for (uint32_t i = 0; i < sizeof(CS_PINS); i++) {
        digitalWrite(i, HIGH); // Bring all CS Lines HIGH (disabled).
    }
  
    digitalWrite(target, LOW); // Bring target CS Line LOW.
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
