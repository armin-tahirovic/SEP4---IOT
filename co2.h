#pragma once
#include "freeRtos.h"
#include "task.h"
#include "Room.h"

typedef struct CO2* pCO2;

int co2_create();
void co2_destroy(pCO2 self);
void meassure(pCO2 self);
int getCO2(pCO2 self);
void task_CO2(void* pvParameters);
