/* timer_util.cpp — 1 ms system tick + heartbeat (GPIO48) */
#include "timer_util.h"
#include <Arduino.h>
#include "scheduler.h"
#include "config.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static void vTimerTask(void *pv) {
  static uint16_t hb = 0;
  bool led = false;
  for (;;) {
    SCH_Update();                     // coop‑scheduler tick (1 ms)
    if (++hb >= 1000) {               // 1‑second heartbeat
      led = !led;
      digitalWrite(PIN_LED_BOARD, led);
      hb = 0;
    }
    vTaskDelay(pdMS_TO_TICKS(1));     // 1 ms period
  }
}

void Timer_Init() {
  pinMode(PIN_LED_BOARD, OUTPUT);
  xTaskCreatePinnedToCore(vTimerTask, "TIMER_ISR", 2048, nullptr, 2, nullptr, APP_CPU_NUM);
}