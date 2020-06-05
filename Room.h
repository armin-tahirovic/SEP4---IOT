#pragma once

#include <ATMEGA_FreeRTOS.h>

#include <queue.h>

#include <lora_driver.h>

#include <hih8120.h>
#include <tsl2591.h>
#include <hcSr501.h>
#include <mh_z19.h>

#include "co2.h"
#include "humidity.h"
#include "motion.h"
#include "window.h"
#include "loraWanDriver.h"

#include "event_groups.h"

static lora_payload_t uplink_message;

QueueHandle_t loraWan_Queue;


#define BIT_0 ( 1 << 0)
#define BIT_1 ( 1 << 1)
#define BIT_2 (1 << 2)
#define BIT_3 (1 << 3)


void* room_co2_sensor;
void* room_humidity_sensor;
void* room_motion_sensor;
void* room_window;

void room_destroy();

void room_decode(lora_payload_t downlink_message);
void room_setThresholdHumidityMax(uint16_t newValue);

void task_RoomCollect(void* pvParameters);

