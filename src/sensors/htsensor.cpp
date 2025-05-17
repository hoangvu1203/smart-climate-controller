#include "htsensor.h"
#include <DHT.h>
#include "config.h"

#define DHTTYPE DHT21
static DHT dht(PIN_DHT_DATA, DHTTYPE);

void HTSensor_Init() {
  dht.begin();
}

bool HTSensor_Read(float &t, float &h) {
  t = dht.readTemperature();
  h = dht.readHumidity();
  return !(isnan(t) || isnan(h));
}