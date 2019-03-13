#include "util.h"
#include <arduino.h>

void switchSPI(int enabled, int disabled) { // Switch which SPI Device is being used.
  digitalWrite(enabled, HIGH);
  digitalWrite(disabled, HIGH);
  
  digitalWrite(enabled, LOW);
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
