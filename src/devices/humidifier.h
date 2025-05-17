#ifndef HUMIDIFIER_H
#define HUMIDIFIER_H
#include <Arduino.h>

void Humidifier_Init();
void Humidifier_Start();          // kick-off one GREEN→YELLOW→RED cycle
bool Humidifier_Active();         // true while a cycle is running
void Humidifier_SetHumidity(float h);   // pass current %RH to module

#endif