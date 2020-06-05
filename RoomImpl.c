#include "Room.h"

uint16_t room_co2_meassure;
int16_t room_temperature_meassure;
uint16_t room_humidity_meassure;
uint8_t room_motion_meassure;

uint8_t maxThreshold_co2;
uint8_t minThreshold_co2;
uint16_t maxThreshold_hum;
uint8_t minThreshold_hum;
uint8_t maxThreshold_temp;
uint8_t minThreshold_temp;



void room_destroy() {
	co2_destroy(room_co2_sensor);
	humidity_destroy(room_humidity_sensor);
	motion_destroy(room_motion_sensor);
	window_destroy(room_window);
}

void room_decode(lora_payload_t downlink_message){
	uint16_t _newValue = 0;
	switch (downlink_message.port_no)
	{
		case 2:
		printf("From DW \n");
		_newValue = downlink_message.bytes[0] << 8;
		_newValue |= downlink_message.bytes[1];
		printf("byte1 %d \n", _newValue);
		_newValue = downlink_message.bytes[2] << 8;
		_newValue |= downlink_message.bytes[3];
		printf("byte2 %d \n", _newValue);
		_newValue = downlink_message.bytes[4] << 8;
		_newValue |= downlink_message.bytes[5];
		printf("byte3 %d \n", _newValue);
		break;
		
		case 3:
		printf("Change threshold humidity min \n");
		break;
		
		case 4:
		printf("Change threshold humidity max \n");
		_newValue = downlink_message.bytes[0] << 8;
		_newValue |= downlink_message.bytes[1];
		printf("new value for humidity max: %d \n", _newValue);
		break;
		
		case 5:
		printf("Change threshold temperature min \n");
		break;
		
		case 6:
		printf("Change threshold temperature max \n");
		break;
		
		case 7:
		printf("Change threshold co2 min \n");
		break;
		
		case 8:
		printf("Change threshold co2 max \n");
		break;
	}
}

void room_setThresholdHumidityMax(uint16_t newValue){
	maxThreshold_hum = newValue;
	
}


void task_RoomCollect(void* pvParameters) {
	(void)pvParameters;
	
	
   uplink_message.len = 7;
   uplink_message.port_no = 2;
   

		for (;;) {
				vTaskDelay(pdMS_TO_TICKS(10000));
			

				room_co2_meassure = getCO2(room_co2_sensor);
				room_humidity_meassure = getHumidity(room_humidity_sensor);
				room_temperature_meassure = getTemperature(room_humidity_sensor);
				room_motion_meassure = getActivity(room_motion_sensor);
			
				
			
				 uplink_message.bytes[0] = room_humidity_meassure >> 8;
				 uplink_message.bytes[1] = room_humidity_meassure & 0xFF;
				 uplink_message.bytes[2] = room_temperature_meassure >> 8;
				 uplink_message.bytes[3] = room_temperature_meassure & 0xFF;
				 uplink_message.bytes[4] = room_co2_meassure >> 8;
				 uplink_message.bytes[5] = room_co2_meassure & 0xFF;
				  uplink_message.bytes[6] = room_motion_meassure;
				 
				xQueueSend(loraWan_Queue, (void*)&uplink_message, portMAX_DELAY);
	
				
			printf("CO2: %d \n Humidity: %d \n Temperature %d \n activity: %d \n", room_co2_meassure, room_humidity_meassure, room_temperature_meassure, room_motion_meassure);
		
			}
		}
		
	
