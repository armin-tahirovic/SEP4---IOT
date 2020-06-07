#pragma once
#include <ATMEGA_FreeRTOS.h>
#include <hih8120.h>
#include <stdint.h>
#include <stdio.h>
#include <task.h>
#include "eventGroups.h"
#include "semaphores.h"

typedef struct humidity* pHumidity;

pHumidity humidity_create();
void humidity_destroy(pHumidity self);

void humidity_meassure(pHumidity self);

int16_t getTemperature(pHumidity self);
void setTemperature(pHumidity self, int16_t newTemperature);

uint16_t getHumidity(pHumidity self);
void setHumidity(pHumidity self, uint16_t newMeasure);

void task_Humidity(void* pvParameters);
