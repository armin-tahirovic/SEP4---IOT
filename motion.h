#pragma once
#include <ATMEGA_FreeRTOS.h>
#include "Room.h"

hcSr501_p hcSr501Inst;

typedef struct MOTION* pMOTION;

pMOTION motion_create();
void motion_destroy(pMOTION self);
void motion_meassure(pMOTION self);
uint8_t getActivity(pMOTION self);
void setActivity(pMOTION self, uint8_t newActivity);

void task_MOTION(void* pvParameters);
