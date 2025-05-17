#include "heater.h"
#include "config.h"
#include "led_codec.h"

static HeaterState curr = HEAT_GREEN;

void Heater_Init() {
  pinMode(PIN_HEAT_B1, OUTPUT);
  pinMode(PIN_HEAT_B0, OUTPUT);
  Heater_Set(HEAT_GREEN);
}

void Heater_Set(HeaterState s) {
  curr = s;
  static const uint8_t lut[] = { 0b10, /*GREEN*/ 0b01, /*ORANGE*/ 0b11 /*RED*/ };
  writeColour(PIN_HEAT_B1, PIN_HEAT_B0, lut[s]);
}
