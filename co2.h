#pragma once

#include <ATMEGA_FreeRTOS.h>
#include <mh_z19.h>
#include <stdio.h>
#include <task.h>

uint16_t new_co2_meassure;


typedef struct CO2* pCO2;

pCO2 co2_create();
void co2_destroy(pCO2 self);
void co2_meassure();
uint16_t getCO2(pCO2 self);
void setCO2(pCO2 self, uint16_t ppm);

void task_CO2(void* pvParameters);




EventGroupHandle_t xEventGroup;
SemaphoreHandle_t xSemaphore;
