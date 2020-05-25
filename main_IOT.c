#include "FreeRTOS.h"
#include "co2.h"

#define TASK_MY_FIRST_PRIORITY (tskIDLE_PRIORITY + 1)
#define TASK_MY_SECOND_PRIORITY (tskIDLE_PRIORITY + 5)
#define TASK_LORA_DRIVER (tskIDLE_PRIORITY + 10)

#define TASK_MY_FIRST_STACK (configMINIMAL_STACK_SIZE)
#define TASK_MY_SECOND_STACK (configMINIMAL_STACK_SIZE)

int main_IOT() {
  co2_sensor = co2_create();
  /*pHumidity humiditySensor = humidity_create();
  xEventGroupSensor = xEventGroupCreate();
  xSemaphoreMutex = xSemaphoreCreateMutex();*/

  /*xTaskCreate(
    taskLoraDriver,
    "LoraDriver",
    TASK_MY_FIRST_STACK,
    NULL,
    TASK_LORA_DRIVER,
    NULL);*/

  xTaskCreate(
    task_CO2,
    "CO2 sensor",
    TASK_MY_SECOND_STACK,
    NULL,
    TASK_MY_SECOND_PRIORITY,
    NULL);

  /*xTaskCreate(
    task_Humidity,
    "Sensor2",
    TASK_MY_SECOND_STACK,
    humiditySensor,
    TASK_MY_SECOND_PRIORITY,
    NULL);*/

  xTaskCreate(
    taskRoomCollect,
    "Rooms",
    TASK_MY_FIRST_STACK,
    NULL,
    TASK_MY_FIRST_PRIORITY,
    NULL);

  vTaskStartScheduler();
  for (;;);
}
