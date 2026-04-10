#include <Arduino.h>
#include "display.h"
#include "simulator.h"
#include "buzzer.h"

#define BUZZER_PIN PA0
#define DISTANCE_STEP 100.0  // 100m

float last_km = 0;

void setup() {
    display_init();
    simulator_init();
    buzzer_init(BUZZER_PIN);
}

void loop() {
    RunData data = simulator_update();

    display_show(data);

    float current_km = data.distance / DISTANCE_STEP;

    if ((int)current_km > (int)last_km) {
        buzzer_trigger(); // KHÔNG block
        last_km = current_km;
    }

    buzzer_update(); // chạy nền

    delay(1000);
}