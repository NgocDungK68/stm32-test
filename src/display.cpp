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

void display_show(RunData data) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // Distance
    display.setCursor(0, 0);
    display.print("Distance: ");
    display.print(data.distance / 1000.0, 2);
    display.println(" km");

    // Time
    int min = data.seconds / 60;
    int sec = data.seconds % 60;

    display.setCursor(0, 20);
    display.print("Time: ");
    display.print(min);
    display.print(":");
    if (sec < 10) display.print("0");
    display.println(sec);

    // Pace động
    int pace_min = (int)data.pace;
    int pace_sec = (int)((data.pace - pace_min) * 60);

    display.setCursor(0, 40);
    display.print("Pace: ");
    display.print(pace_min);
    display.print(":");
    if (pace_sec < 10) display.print("0");
    display.print(pace_sec);
    display.println(" /km");

    display.display();
}