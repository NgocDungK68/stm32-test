#ifndef GPS_H
#define GPS_H

struct GPSData {
    bool valid;
    bool hasSignal;   // 🔥 có data từ GPS hay không
    float lat;
    float lon;
    float speed_kmph;
};

void gps_init();
GPSData gps_update();

#endif