#include "buzzer.h"
#include <Arduino.h>

static int buzzerPin;
static bool active = false;
static int beep_count = 0;
static bool state = false;
static unsigned long lastToggle = 0;

void buzzer_init(int pin) {
    buzzerPin = pin;
    pinMode(buzzerPin, OUTPUT);
}

void buzzer_start() {
    active = true;
    beep_count = 0;
    state = true;
    digitalWrite(buzzerPin, HIGH);
    lastToggle = millis();
}

void buzzer_update() {
    if (!active) return;

    unsigned long now = millis();

    if (now - lastToggle >= 1000) {
        lastToggle = now;

        state = !state;
        digitalWrite(buzzerPin, state ? HIGH : LOW);

        if (!state) beep_count++;

        if (beep_count >= 3) {
            active = false;
            digitalWrite(buzzerPin, LOW);
        }
    }
}