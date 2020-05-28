#include <ATMEGA_FreeRTOS.h>
#include "co2.h"
#include <hih8120.h>
#include <tsl2591.h>


#define TASK_MY_FIRST_PRIORITY (tskIDLE_PRIORITY + 1)
#define TASK_MY_SECOND_PRIORITY (tskIDLE_PRIORITY + 5)
#define TASK_LORA_DRIVER (tskIDLE_PRIORITY + 10)

#define TASK_MY_FIRST_STACK (configMINIMAL_STACK_SIZE)
#define TASK_MY_SECOND_STACK (configMINIMAL_STACK_SIZE)

void task2( void *pvParameters );

void create_tasks()
{
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

  xTaskCreate(
    task_Humidity,
    "Sensor2",
    TASK_MY_SECOND_STACK,
    NULL,
    TASK_MY_SECOND_PRIORITY,
    NULL);

  xTaskCreate(
    taskRoomCollect,
    "Rooms",
    TASK_MY_FIRST_STACK,
    NULL,
    TASK_MY_FIRST_PRIORITY,
    NULL);
	
	xTaskCreate(
	task2
	,  (const portCHAR *)"Task2"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

uint16_t ppm = 0;

void my_co2_call_back(uint16_t ppm){
	setCO2(co2_sensor, ppm);
	uint16_t sensor_value = getCO2(co2_sensor);
	printf("ppm: %d \n", sensor_value);
}


void task2( void *pvParameters )
{
	#if (configUSE_APPLICATION_TASK_TAG == 1)
	// Set task no to be used for tracing with R2R-Network
	vTaskSetApplicationTaskTag( NULL, ( void * ) 2 );
	#endif

	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 1000/portTICK_PERIOD_MS; // 1000 ms

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	
	uint16_t max_hum_setting; // Max Humidity
	int16_t max_temp_setting; // Max Temperature
	
lora_payload_t downlink_payload;
	for(;;)
	{
xMessageBufferReceive(down_link_message_buffer_handle, &downlink_payload, sizeof(lora_payload_t), portMAX_DELAY);
printf("DOWN LINK: from port: %d with %d bytes received!", downlink_payload.port_no, downlink_payload.len); // Just for Debug

if (4 == downlink_payload.len) // Check that we have got the expected 4 bytes
{
	// decode the payload into our variales
	max_hum_setting = (downlink_payload.bytes[0] << 8) + downlink_payload.bytes[1];
	max_temp_setting = (downlink_payload.bytes[2] << 8) + downlink_payload.bytes[3];
}

	}
}


uint16_t main_IOT() {
  co2_sensor = co2_create();
  humidity_sensor = humidity_create();
  mh_z19_create(ser_USART3, my_co2_call_back);
  hih8120Create();


  /*xEventGroupSensor = xEventGroupCreate();
  xSemaphoreMutex = xSemaphoreCreateMutex();*/

 create_tasks();

  vTaskStartScheduler();
  for (;;);
}
