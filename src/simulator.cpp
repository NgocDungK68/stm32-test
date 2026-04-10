#include "simulator.h"
#include <Arduino.h>

static float distance = 0;
static int seconds = 0;
static float pace = 4.0; // min/km

void simulator_init() {
    distance = 0;
    seconds = 0;
    pace = 4.0;
}

RunData simulator_update() {
    seconds++;

    // random dao động nhỏ quanh 4:00
    float delta = random(-5, 6) / 100.0; // -0.05 → +0.05
    pace += delta;

    // giới hạn pace (3:50 → 4:10)
    if (pace < 3.83) pace = 3.83;
    if (pace > 4.17) pace = 4.17;

    // tính speed từ pace (m/s)
    float speed = 1000.0 / (pace * 60.0);

    distance += speed;

    RunData data;
    data.distance = distance;
    data.seconds = seconds;
    data.pace = pace;

    return data;
}