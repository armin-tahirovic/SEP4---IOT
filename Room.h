#pragma once

#include <ATMEGA_FreeRTOS.h>

#include <lora_driver.h>

#include <hih8120.h>
#include <tsl2591.h>
#include <hcSr501.h>
#include <mh_z19.h>

#include "semaphores.h"

#include "co2.h"
#include "humidity.h"
#include "motion.h"
#include "window.h"
#include "loraWanDriver.h"

#include "eventGroups.h"
#include "custom_queues.h"

static lora_payload_t uplink_message;



void* room_co2_sensor;
void* room_humidity_sensor;
void* room_motion_sensor;
void* room_window;

void room_destroy();

void room_decode(lora_payload_t downlink_message);
void room_setThresholdHumidityMax(uint16_t newValue);

void task_RoomCollect(void* pvParameters);
