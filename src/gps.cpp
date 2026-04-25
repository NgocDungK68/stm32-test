#include "gps.h"
#include <TinyGPS++.h>
#include <Arduino.h>

TinyGPSPlus gps;

HardwareSerial SerialGPS(USART2);

static unsigned long lastSignalTime = 0;

void gps_init() {
    SerialGPS.begin(9600);
}

GPSData gps_update() {  
    GPSData data;
    data.valid = false;
    data.hasSignal = false;
    data.lat = 0;
    data.lon = 0;
    data.speed_kmph = 0;

    while (SerialGPS.available()) {
        char c = SerialGPS.read();

        Serial.write(c);   // 🔥 debug NMEA ra Serial Monitor

        gps.encode(c);
        lastSignalTime = millis();
    }

    // 🔥 fix NO DATA nhảy loạn (GPS gửi 1Hz)
    data.hasSignal = (millis() - lastSignalTime < 2000);

    if (gps.location.isValid()) {
        data.valid = true;
        data.lat = gps.location.lat();
        data.lon = gps.location.lng();
        data.speed_kmph = gps.speed.kmph();
    }

    return data;
}