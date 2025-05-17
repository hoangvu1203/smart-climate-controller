#include <Arduino.h>
#include "scheduler.h"
#include "htsensor.h"
#include "light_control.h"
#include "timer_util.h"

#include <DHT.h>
#include "config.h"

#define DHTTYPE DHT21
static DHT dht(PIN_DHT_DATA, DHTTYPE);

/* 5 s sensor sampling task */
static void task_ReadSensors() {
  static uint32_t seq = 0;
  float temp, hum;
  if (HTSensor_Read(temp, hum)) {
    Serial.printf("[%lu]  T = %.1f °C,  H = %.1f %%RH\n", seq++, temp, hum);
    LightControl_Update(temp, hum);
  } else {
    Serial.println("[sensor] read error");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Smart Climate Control – booting…\n");

  SCH_Init();
  /* schedule tasks */
  SCH_Add_Task(task_ReadSensors, 0, 5000);  // every 5 s
  Timer_Init();             

  HTSensor_Init();
  LightControl_Init();
}

void loop() {
  SCH_Dispatch_Tasks();  // run due tasks; non‑blocking
}
