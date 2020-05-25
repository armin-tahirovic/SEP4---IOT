#pragma once
#include "FreeRTOS.h"
#include "task.h"
#include "co2.h"

typedef struct Room* pRoom;

void* co2_sensor;

pRoom room_create();
void room_destroy(pRoom self);
void taskRoomCollect(void* pvParameters);
