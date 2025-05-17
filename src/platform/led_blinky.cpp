#include <Arduino.h>
#include "led_blinky.h"
#include "config.h"

void LED_Blinky_Init() {
  pinMode(PIN_LED_BOARD, OUTPUT);
}