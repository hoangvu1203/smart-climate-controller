#include <Arduino.h>
#include "humidifier.h"
#include "config.h"
#include "led_codec.h"
#include "scheduler.h"

static const uint32_t T_GREEN  = 5000;   // ms
static const uint32_t T_YELLOW = 3000;
static const uint32_t T_RED    = 2000;

enum Phase : uint8_t { IDLE, GREEN, YELLOW, RED };
static Phase    phase     = IDLE;
static uint32_t ticksLeft = 0;           // ms left in current phase

static inline void setLED(uint8_t code)
{
    writeColour(PIN_HUM_B1, PIN_HUM_B0, code);
}

/* 1-ms FSM task (runs every scheduler tick) */
static void fsmTask()
{
    switch (phase)
    {
    case IDLE:
        /* nothing to do */
        break;

    case GREEN:
    case YELLOW:
    case RED:
        if (ticksLeft) --ticksLeft;
        if (ticksLeft == 0)
        {
            if (phase == GREEN) {            // → YELLOW
                phase     = YELLOW;
                ticksLeft = T_YELLOW;
                setLED(0b01);
            }
            else if (phase == YELLOW) {      // → RED
                phase     = RED;
                ticksLeft = T_RED;
                setLED(0b11);
            }
            else {                           // RED finished → IDLE
                phase = IDLE;
                setLED(0b00);
            }
        }
        break;
    }
}

/* public API */
void Humidifier_Init()
{
    pinMode(PIN_HUM_B1, OUTPUT);
    pinMode(PIN_HUM_B0, OUTPUT);
    setLED(0b00);

    /* run FSM every scheduler tick (1 ms) */
    SCH_Add_Task(fsmTask, 0, 1);
}

bool Humidifier_Active()
{
    return phase != IDLE;
}

void Humidifier_Start()
{
    if (phase != IDLE) return;      // already flashing

    phase     = GREEN;
    ticksLeft = T_GREEN;
    setLED(0b10);
}

