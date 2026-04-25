#ifndef DISPLAY_H
#define DISPLAY_H

void display_init();

void display_show(
    float distance,
    int seconds,
    float pace,
    bool gps_valid,
    bool gps_signal,   // 🔥 thêm
    float lat,
    float lon
);

#endif