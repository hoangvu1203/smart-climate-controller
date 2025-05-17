#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

constexpr uint8_t PIN_LED_BOARD = 48;

/* Heater block */
constexpr uint8_t PIN_HEAT_B1   = 6;
constexpr uint8_t PIN_HEAT_B0   = 7;    // LSB

/* Cooler block */
constexpr uint8_t PIN_COOL_B1   = 8;
constexpr uint8_t PIN_COOL_B0   = 9;

/* Humidifier block */
constexpr uint8_t PIN_HUM_B1    = 10;
constexpr uint8_t PIN_HUM_B0    = 17;

/*── DHT21 DATA line ────────────────────────────────────────────*/
constexpr uint8_t PIN_DHT_DATA = A2;

/* Environmental thresholds */
constexpr float  T_LOW_WARN  = 20.0f;  // °C   heater RED (too cold)
constexpr float  T_LOW_SAFE  = 22.0f;  // °C   heater ORANGE warning
constexpr float  T_HIGH_WARN = 28.0f;  // °C   cooler GREEN pulse (too hot)
constexpr float  HUM_LOW = 95.0f;

#endif
