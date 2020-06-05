#include <ATMEGA_FreeRTOS.h>
#include "Room.h"

#include <lora_driver.h>

#define TASK_MY_FIRST_PRIORITY (tskIDLE_PRIORITY + 15)
#define TASK_MY_SECOND_PRIORITY (tskIDLE_PRIORITY + 5)
#define TASK_LORA_DRIVER (tskIDLE_PRIORITY + 10)

#define TASK_MY_FIRST_STACK (configMINIMAL_STACK_SIZE)
#define TASK_MY_SECOND_STACK (configMINIMAL_STACK_SIZE)



void create_tasks()
{

	  xTaskCreate(
		task_RoomCollect,
		"Rooms",
		TASK_MY_FIRST_STACK,
		NULL,
		TASK_MY_FIRST_PRIORITY,
		NULL);
	
		  xTaskCreate(
		  task_CO2,
		  "CO2 sensor",
		  TASK_MY_SECOND_STACK,
		  NULL,
		  TASK_MY_SECOND_PRIORITY,
		  NULL);

		  xTaskCreate(
		  task_Humidity,
		  "Humidity sensor",
		  TASK_MY_SECOND_STACK,
		  NULL,
		  TASK_MY_SECOND_PRIORITY,
		  NULL);
		  
		  xTaskCreate(
		  task_MOTION,
		  "motion sensor",
		  TASK_MY_SECOND_STACK,
		  NULL,
		  TASK_MY_SECOND_PRIORITY,
		  NULL);
	
}



uint16_t main_IOT() {

		room_window = window_create();
		room_co2_sensor = co2_create();
		room_humidity_sensor = humidity_create();
		room_motion_sensor = motion_create();
		
		
		loraWan_Queue = xQueueCreate(10, sizeof(lora_payload_t));
		
	create_tasks();


  vTaskStartScheduler();
  for (;;);
}
