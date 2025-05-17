#include "light_control.h"
#include "heater.h"
#include "cooler.h"
#include "humidifier.h"
#include "config.h"
#include "scheduler.h"

static void coolerOffTask() { Cooler_Set(COOL_OFF); }

void LightControl_Init() {
  Heater_Init();
  Cooler_Init();
  Humidifier_Init();
}

void LightControl_Update(float t, float h) {
  /*──────── Temperature logic ────────*/
  if (t < T_LOW_WARN) {
    Heater_Set(HEAT_RED);
  } else if (t < T_LOW_SAFE) {
    Heater_Set(HEAT_ORANGE);
  } else {
    Heater_Set(HEAT_GREEN);
  }

  if (t <= T_HIGH_WARN) {
    Cooler_Set(COOL_OFF);
  } else{
    Cooler_Set(COOL_GREEN);
    SCH_Add_Task(coolerOffTask, 5000, 0);      // run cooler 5 s then off
  }

  /*──────── Humidity logic ───────────*/
  if (h < HUM_LOW && !Humidifier_Active())
    Humidifier_Start();           // first time only – repeats handled internally
}