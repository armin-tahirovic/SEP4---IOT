#pragma once
#include "Room.h"

typedef struct CO2* pCO2;

uint16_t co2_create();
void co2_destroy(pCO2 self);
void co2_meassure(pCO2 self);
uint16_t getCO2(pCO2 self);
void setCO2(pCO2 self, uint16_t ppm);
void task_CO2(void* pvParameters);
