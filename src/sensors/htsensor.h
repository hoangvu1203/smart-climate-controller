#ifndef HTSENSOR_H
#define HTSENSOR_H
#include <Arduino.h>

void HTSensor_Init();
bool HTSensor_Read(float &t, float &h);       // returns false on error

#endif