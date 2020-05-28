#pragma once
#include <ATMEGA_FreeRTOS.h>
#include <stdint.h>
#include "task.h"

typedef struct humidity* pHumidity;

int humidity_create();

void humidity_meassure(pHumidity self);

uint16_t getHumidity(pHumidity self);

void setHumidity(pHumidity self, uint16_t newMeasure);

void task_Humidity(void* pvParameters);
