

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

#define mainCREATE_SIMPLE_BLINKY_DEMO_ONLY	1

#define mainREGION_1_SIZE	8201
#define mainREGION_2_SIZE	29905
#define mainREGION_3_SIZE	7607



extern void main_IOT( void );
extern void main_full( void );



StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];


static BaseType_t xTraceRunning = pdTRUE;

uint16_t ppm;

void my_co2_call_back(uint16_t ppm){
	printf("ppm: %d \n", ppm);
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
	
	
	// Create LoRaWAN task and start it up with priority 3
	lora_handler_create(3, down_link_message_buffer_handle);
	
		hih8120Create();
		//mh_z19_create(ser_USART3, my_co2_call_back);
	

	
}


int main( void )
{
	

	//prvInitialiseHeap();
	

	#if ( mainCREATE_SIMPLE_BLINKY_DEMO_ONLY == 1 )
	{
		initialiseSystem();
		main_IOT();
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

