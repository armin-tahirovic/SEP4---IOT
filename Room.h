#pragma once
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include "co2.h"
#include "humidity.h"
#include "CO2.h"
#include "loraWanDriver.h"

typedef struct Room* pRoom;

void* co2_sensor;
void* humidity_sensor;

void taskRoomCollect(void* pvParameters);
