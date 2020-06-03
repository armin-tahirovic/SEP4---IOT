#include "Room.h"

QueueHandle_t xQueue;

typedef struct LoraDriver* pLora;
typedef struct LoraDriver {
  uint8_t len;
  uint8_t* bytes;
} LoraDriver_t;

void queueCreate();
void queue_lora(pLora mes);
void taskLoraDriver(void* pvParameters);
