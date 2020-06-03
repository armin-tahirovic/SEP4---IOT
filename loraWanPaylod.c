#include "loraWanDriver.h"

void queueCreate() {
  xQueue = xQueueCreate(10, sizeof(pLora));
}

void queue_lora(pLora mes) {
  xQueueSend(
    xQueue,
    &mes,
    0u);
}

void taskLoraDriver(void* pvParameters) {
  queueCreate();
  (void)pvParameters;
  pLora message = pvParameters;

  for (;;)
  {
    BaseType_t em = xQueueReceive(
      xQueue,
      &message,
      5000);

    em = pdTRUE;

    /*xSemaphoreTake(xSemaphoreMutex, portMAX_DELAY);
    printf("Length: %i \n", message->len);
    xSemaphoreGive(xSemaphoreMutex);

    xSemaphoreTake(xSemaphoreMutex, portMAX_DELAY);
    for (size_t i = 0; i < message->len; i++)
    {
      printf("Bytes: %x \n", message->bytes[i]);
    }
    xSemaphoreGive(xSemaphoreMutex);*/

    vPortFree(message->bytes);
    vPortFree(message);
  }
}
