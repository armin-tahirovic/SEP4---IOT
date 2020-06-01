#pragma once
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include "co2.h"
#include "humidity.h"
#include "CO2.h"

typedef struct Room* pRoom;

void* co2_sensor;
void* humidity_sensor;

pRoom room_create();
void room_destroy(pRoom self);
void taskRoomCollect(void* pvParameters);
