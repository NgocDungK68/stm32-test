#include "display.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void display_init() {
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.clearDisplay();
}

void display_show(
    float distance,
    int seconds,
    float pace,
    bool gps_valid,
    bool gps_signal,
    float lat,
    float lon
) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // 1. Distance
    display.setCursor(0, 0);
    display.print("Dist: ");
    display.print(distance / 1000.0, 2);
    display.println(" km");

    // 2. Time
    display.setCursor(0, 10);
    display.print("Time: ");
    display.print(seconds / 60);
    display.print(":");
    int sec = seconds % 60;
    if (sec < 10) display.print("0");
    display.println(sec);

    // 3. Pace
    display.setCursor(0, 20);
    display.print("Pace: ");
    if (pace > 0) {
        int min = (int)pace;
        int secp = (int)((pace - min) * 60);
        display.print(min);
        display.print(":");
        if (secp < 10) display.print("0");
        display.print(secp);
        display.println("/km");
    } else {
        display.println("--");
    }

    // 4. GPS Status
    display.setCursor(0, 30);
    display.print("GPS: ");

    if (!gps_signal) {
        display.println("NO DATA");   // không có UART
    } else if (!gps_valid) {
        display.println("NO FIX");    // chưa bắt vệ tinh
    } else {
        display.println("OK");        // có fix
    }

    // 5. Lat + Lon
    display.setCursor(0, 40);

    if (gps_valid) {
        display.print("Lat:");
        display.println(lat, 5);

        display.setCursor(0, 50);
        display.print("Lon:");
        display.println(lon, 5);
    } else {
        display.println("NO GPS");
    }

    display.display();
}