#include "buzzer.h"
#include <Arduino.h>

static int buzzerPin;

static bool active = false;
static int step = 0;
static unsigned long lastTime = 0;

void buzzer_init(int pin) {
    buzzerPin = pin;
    pinMode(buzzerPin, OUTPUT);
}

void buzzer_trigger() {
    active = true;
    step = 0;
    lastTime = millis();
}

void buzzer_update() {
    if (!active) return;

    unsigned long now = millis();

    // mỗi bước 1 giây
    if (now - lastTime >= 1000) {
        lastTime = now;
        step++;

        if (step % 2 == 1) {
            digitalWrite(buzzerPin, HIGH);
        } else {
            digitalWrite(buzzerPin, LOW);
        }

        // 3 tiếng => 6 step (on/off)
        if (step >= 6) {
            digitalWrite(buzzerPin, LOW);
            active = false;
        }
    }
}