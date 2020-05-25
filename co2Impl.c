#include "co2.h"

typedef struct CO2 {
  int driverPort;
  int co2;
}CO2_t;

int co2_create() {
  pCO2 driverPort = (pCO2)pvPortMalloc(sizeof(CO2_t));

  if (NULL == driverPort)
    return NULL;

  return driverPort;

}

void co2_destroy(pCO2 self) {
  vPortFree(self);
}

void meassure(pCO2 self) {
  self->co2 = rand() % 50;
}

int getCO2(pCO2 self) {

  return self->co2;
}

void task_CO2(void* pvParameters) {
  (void)pvParameters;

  for (;;) {
    vTaskDelay(pdMS_TO_TICKS(200));
    meassure(co2_sensor);
  }
}
