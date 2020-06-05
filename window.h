#pragma once
#include <ATMEGA_FreeRTOS.h>
#include <rcServo.h>

#include "Room.h"
#include <stdbool.h>

typedef struct WINDOW* pWINDOW;

pWINDOW window_create();
void window_destroy(pWINDOW self);
bool window_getIsOpen(pWINDOW self);
void window_setIsOpen(pWINDOW self, bool isOpen);
void window_close(pWINDOW self);
void window_open(pWINDOW self);
