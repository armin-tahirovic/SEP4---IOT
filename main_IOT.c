#include <ATMEGA_FreeRTOS.h>
#include "Room.h"

#include <lora_driver.h>

uint16_t main_IOT() {

		room_window = window_create();
		room_co2_sensor = co2_create();
		room_humidity_sensor = humidity_create();
		room_motion_sensor = motion_create();
		
		loraWan_Queue = xQueueCreate(10, sizeof(lora_payload_t));

}
