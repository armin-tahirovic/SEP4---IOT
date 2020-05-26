#pragma once
#include "freeRtos.h"
#include <stdint.h>
#include "task.h"

typedef struct motion* pMotion;

int motion_create();

void motion_meassure(pMotion self);

uint16_t getMotion(pMotion self);


