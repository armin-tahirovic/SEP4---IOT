

/* Standard includes. */
#include <stdlib.h>

#include <stdio.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include <hal_defs.h>
#include <ihal.h>



#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#include <FreeRTOSTraceDriver.h>
#include <stdio_driver.h>
#include <serial.h>

#include <hih8120.h>
#include <tsl2591.h>
#include <hcSr501.h>
#include <mh_z19.h>


// Needed for LoRaWAN
#include <lora_driver.h>

#include "task.h"
#include "Room.h"

#define mainCREATE_SIMPLE_BLINKY_DEMO_ONLY	1

#define mainREGION_1_SIZE	8201
#define mainREGION_2_SIZE	29905
#define mainREGION_3_SIZE	7607

#define TASK_MY_FIRST_PRIORITY (tskIDLE_PRIORITY + 15)
#define TASK_MY_SECOND_PRIORITY (tskIDLE_PRIORITY + 5)
#define TASK_LORA_DRIVER (tskIDLE_PRIORITY + 10)

#define TASK_MY_FIRST_STACK (configMINIMAL_STACK_SIZE)
#define TASK_MY_SECOND_STACK (configMINIMAL_STACK_SIZE)


extern void main_IOT( void );
extern void main_full( void );



StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];


static BaseType_t xTraceRunning = pdTRUE;



hcSr501_p hcSr501Inst = NULL;

void my_co2_call_back(uint16_t ppm){
	printf("ppm: %d \n", ppm);
	setCO2(room_co2_sensor, ppm);
}

void create_tasks_and_semaphores(void)
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
	  room_co2_sensor,
	  TASK_MY_SECOND_PRIORITY,
	  NULL);
	  
	  

	  xTaskCreate(
	  task_Humidity,
	  "Humidity sensor",
	  TASK_MY_SECOND_STACK,
	  room_humidity_sensor,
	  TASK_MY_SECOND_PRIORITY,
	  NULL);
	  
	  xTaskCreate(
	  task_MOTION,
	  "motion sensor",
	  TASK_MY_SECOND_STACK,
	  room_motion_sensor,
	  TASK_MY_SECOND_PRIORITY,
	  NULL);
	  
	  	if ( xSemaphore_hum == NULL )  // Check to confirm that the Semaphore has not already been created.
	  	{
		  	xSemaphore_hum = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		  	if ( ( xSemaphore_hum ) != NULL )
		  	{
			  	xSemaphoreGive( ( xSemaphore_hum ) );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		  	}
	  	}
	  
	    	if ( xSemaphore_co2 == NULL )  // Check to confirm that the Semaphore has not already been created.
	    	{
		    	xSemaphore_co2 = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		    	if ( ( xSemaphore_co2 ) != NULL )
		    	{
			    	xSemaphoreGive( ( xSemaphore_co2 ) );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		    	}
	    	}
			
}

void initialiseSystem()
{
	
	// Set output ports for leds used in the example
	DDRA |= _BV(DDA0) | _BV(DDA7);
	// Initialise the trace-driver to be used together with the R2R-Network
	trace_init();
	// Make it possible to use stdio on COM port 0 (USB) on Arduino board - Setting 57600,8,N,1
	stdioCreate(ser_USART0);
MessageBufferHandle_t down_link_message_buffer_handle = xMessageBufferCreate(sizeof(lora_payload_t)*2); 



	// vvvvvvvvvvvvvvvvv BELOW IS LoRaWAN initialisation vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// Initialise the HAL layer and use 5 for LED driver priority
	hal_create(5);
	// Initialise the LoRaWAN driver without down-link buffer
	lora_driver_create(LORA_USART, down_link_message_buffer_handle);


main_IOT();

// Create LoRaWAN task and start it up with priority 3
//lora_handler_create(1, down_link_message_buffer_handle);


		create_tasks_and_semaphores();
	
		mh_z19_create(ser_USART3, my_co2_call_back);
		
		hih8120Create();
		
		hcSr501Inst = hcSr501Create(&PORTE, PE5);
		if ( NULL == hcSr501Inst )
		{
			printf("driver not created \n");
		} else {
			motion_setSensor(hcSr501Inst);
		}
		
		

	
}


int main( void )
{
	

	//prvInitialiseHeap();
	

	#if ( mainCREATE_SIMPLE_BLINKY_DEMO_ONLY == 1 )
	{
		initialiseSystem();
	
		  vTaskStartScheduler();
	}
	#else
	{
		/* Start the trace recording - the recording is written to a file if
		configASSERT() is called. */
		printf( "\r\nTrace started.\r\nThe trace will be dumped to disk if a call to configASSERT() fails.\r\n" );
		printf( "Uncomment the call to kbhit() in this file to also dump trace with a key press.\r\n" );

		main_full();
	}
	#endif

	return 0;
}

