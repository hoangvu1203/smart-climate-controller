#include "cooler.h"
#include "config.h"
#include "led_codec.h"

static CoolerState curr = COOL_OFF;

void Cooler_Init() {
  pinMode(PIN_COOL_B1, OUTPUT);
  pinMode(PIN_COOL_B0, OUTPUT);
  Cooler_Set(COOL_OFF);
}

void Cooler_Set(CoolerState s) {
  curr = s;
  static const uint8_t lut[] = { 0b00, /*OFF*/ 0b10, /*GREEN*/ 0b11 /*RED*/ };
  writeColour(PIN_COOL_B1, PIN_COOL_B0, lut[s]);
}

CoolerState Cooler_Get() { return curr; }