#pragma once
#include "freeRtos.h"
#include <stdint.h>
#include "task.h"
#include "co2.h"

typedef struct temperature* pTemperature;

int temperature_create();

void temperature_meassure(pTemperature self);

uint16_t getTemperature(pTemperature self);



