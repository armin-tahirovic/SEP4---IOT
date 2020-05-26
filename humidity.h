#pragma once
#include "freeRtos.h"
#include <stdint.h>
#include "task.h"

typedef struct humidity* pHumidity;

int humidity_create();

void humidity_meassure(pHumidity self);

uint16_t gethumidity(pHumidity self);


