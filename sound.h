#pragma once
#include "freeRtos.h"
#include <stdint.h>
#include "task.h"
#include "co2.h"

typedef struct sound* pSound;

int sound_create();

void sound_meassure(pSound self);

uint16_t getSound(pSound self);

