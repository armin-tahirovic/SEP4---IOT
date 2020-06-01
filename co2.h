#pragma once
#include "Room.h"
#include "event_groups.h"
#include "semphr.h"

typedef struct CO2* pCO2;

uint16_t co2_create();
void co2_destroy(pCO2 self);
void co2_meassure(pCO2 self);
uint16_t getCO2(pCO2 self);
void setCO2(pCO2 self, uint16_t ppm);
void task_CO2(void* pvParameters);

#define BIT_0 ( 1 << 0)
#define BIT_1 ( 1 << 2)
#define BIT_2 (1 << 3)
#define BIT_3 (1 << 4)
#define BIT_4 (1 << 5)
EventGroupHandle_t xEventGroup;
SemaphoreHandle_t xSemaphore;
