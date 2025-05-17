#ifndef LED_CODEC_H
#define LED_CODEC_H
#include <Arduino.h>
inline void writeColour(uint8_t pinB1, uint8_t pinB0, uint8_t bits)
{
    digitalWrite(pinB1, (bits & 0b10) ? HIGH : LOW);   // MSB
    digitalWrite(pinB0, (bits & 0b01) ? HIGH : LOW);   // LSB
}
#endif