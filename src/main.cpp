#include <Arduino.h>
#include "display.h"
#include "gps.h"
#include "buzzer.h"

#define BUZZER_PIN PA0

float total_distance = 0;
unsigned long start_time = 0;
bool started = false;

float last_lat = 0;
float last_lon = 0;

float last_mark = 0;

// Haversine
float calcDistance(float lat1, float lon1, float lat2, float lon2) {
    float R = 6371000; // m
    float dLat = radians(lat2 - lat1);
    float dLon = radians(lon2 - lon1);

    lat1 = radians(lat1);
    lat2 = radians(lat2);

    float a = sin(dLat/2)*sin(dLat/2) +
              sin(dLon/2)*sin(dLon/2)*cos(lat1)*cos(lat2);

    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    return R * c;
}

void setup() {
    Serial.setTx(PA9);
    Serial.setRx(PA10);
    Serial.begin(115200);   // debug PC

    display_init();
    gps_init();
    buzzer_init(BUZZER_PIN);

    delay(2000);
    Serial.println("SYSTEM START");
}

void loop() {

    GPSData gpsData = gps_update();

    unsigned long now = millis();

    if (gpsData.valid) {

        if (!started) {
            started = true;
            start_time = now;
            last_lat = gpsData.lat;
            last_lon = gpsData.lon;
        }

        float d = calcDistance(last_lat, last_lon, gpsData.lat, gpsData.lon);

        if (d > 0.5) { // lọc nhiễu
            total_distance += d;
            last_lat = gpsData.lat;
            last_lon = gpsData.lon;
        }
    }

    int elapsed = started ? (now - start_time) / 1000 : 0;

    // pace
    float pace = 0;
    if (gpsData.speed_kmph > 0.5) {
        pace = 60.0 / gpsData.speed_kmph;
    }

    // buzzer mỗi 100m
    float current_step = total_distance / 100.0;
    if ((int)current_step > (int)last_mark) {
        buzzer_start();
        last_mark = current_step;
    }

    display_show(
        total_distance,
        elapsed,
        pace,
        gpsData.valid,
        gpsData.hasSignal,
        gpsData.lat,
        gpsData.lon
    );

    buzzer_update();

    delay(50);
}