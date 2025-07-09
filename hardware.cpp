#include "hardware.h"
#include "config.h"
#include <Arduino.h>

void setupHardware() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(PIR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    
    // Initial state
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
}

void setLED(bool state) {
    digitalWrite(LED_PIN, state);
}

void setBuzzer(bool state, int frequency) {
    if (state) {
        tone(BUZZER_PIN, frequency);
    } else {
        noTone(BUZZER_PIN);
    }
}

bool getPIRState() {
    return digitalRead(PIR_PIN) == HIGH;
}

void stopAllOutputs() {
    setLED(false);
    setBuzzer(false);
}
