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
		minThreshold_hum = room_byteConverter(downlink_message);
		break;
		
		case 4:
		printf("Change threshold humidity max \n");
		maxThreshold_hum = room_byteConverter(downlink_message);
		printf("new value for humidity max: %d \n", maxThreshold_hum);
		break;
		
		case 5:
		printf("Change threshold temperature min \n");
		minThreshold_temp = room_byteConverter(downlink_message);
		break;
		
		case 6:
		printf("Change threshold temperature max \n");
		maxThreshold_temp = room_byteConverter(downlink_message);
		break;
		
		case 7:
		printf("Change threshold co2 min \n");
		minThreshold_co2 = room_byteConverter(downlink_message);
		break;
		
		case 8:
		printf("Change threshold co2 max \n");
		maxThreshold_co2 = room_byteConverter(downlink_message);
		break;
	}
}

uint16_t room_byteConverter(lora_payload_t message){
	uint16_t _newValue = 0;
	
	_newValue = message.bytes[0] << 8;
	_newValue |= message.bytes[1];
	
	return _newValue;
	
	
}

void room_setThresholdHumidityMax(uint16_t newValue){
	maxThreshold_hum = newValue;
	
}


void task_RoomCollect(void* pvParameters) {
	(void)pvParameters;
	
	
   uplink_message.len = 7;
   uplink_message.port_no = 2;
   

		for (;;) {
			EventBits_t uxBits = xEventGroupWaitBits(xEventGroup, BIT_0 | BIT_1, pdTRUE, pdTRUE, 500);

		if ((uxBits & (BIT_0 | BIT_1 )) == (BIT_0 | BIT_1 )){
				vTaskDelay(pdMS_TO_TICKS(5000));
			
				xSemaphoreTake(xSemaphore_co2, portMAX_DELAY);
				room_co2_meassure = getCO2(room_co2_sensor);
					xSemaphoreGive(xSemaphore_co2);
				
				xSemaphoreTake(xSemaphore_hum, portMAX_DELAY);
				room_humidity_meassure = getHumidity(room_humidity_sensor);	
				room_temperature_meassure = getTemperature(room_humidity_sensor);
					xSemaphoreGive(xSemaphore_hum);
					
				room_motion_meassure = getActivity(room_motion_sensor);
				setActivity(room_motion_sensor, 0);
			
				
			
				 uplink_message.bytes[0] = room_humidity_meassure >> 8;
				 uplink_message.bytes[1] = room_humidity_meassure & 0xFF;
				 uplink_message.bytes[2] = room_temperature_meassure >> 8;
				 uplink_message.bytes[3] = room_temperature_meassure & 0xFF;
				 uplink_message.bytes[4] = room_co2_meassure >> 8;
				 uplink_message.bytes[5] = room_co2_meassure & 0xFF;
				  uplink_message.bytes[6] = room_motion_meassure;
				 
				xQueueSend(loraWan_Queue, (void*)&uplink_message, portMAX_DELAY);
				xEventGroupClearBits(xEventGroup, BIT_0 | BIT_1);
				
			printf("CO2: %d \n Humidity: %d \n Temperature %d \n activity: %d \n", room_co2_meassure, room_humidity_meassure, room_temperature_meassure, room_motion_meassure);
		
			}}
		}
