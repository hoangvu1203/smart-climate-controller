#ifndef COOLER_H
#define COOLER_H
#include <Arduino.h>

enum CoolerState { COOL_OFF, COOL_GREEN, COOL_RED };
void Cooler_Init();
void Cooler_Set(CoolerState state);
CoolerState Cooler_Get();
#endif
