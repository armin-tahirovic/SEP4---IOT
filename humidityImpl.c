#include "humidity.h"

typedef struct humidity {
	uint16_t humidity;
	int16_t temperature;
}humidity_t;



pHumidity humidity_create() {
	pHumidity driverPort = (pHumidity)pvPortMalloc(sizeof(humidity_t));

	if (NULL == driverPort) {
		return NULL;
	}

	return driverPort;

}

void humidity_destroy(pHumidity self){
	vPortFree(self);
}

void humidity_meassure(pHumidity self) {
	
	hih8120Meassure();
	
	xSemaphoreTake(xSemaphore_hum, portMAX_DELAY);
	setHumidity(self, hih8120GetHumidityPercent_x10());
	setTemperature(self, hih8120GetTemperature_x10());
	xSemaphoreGive(xSemaphore_hum);
	
	printf("Humidity and temperature: %d and %d \n", self->humidity, self->temperature);
}

int16_t getTemperature(pHumidity self){
	return self->temperature;
}

void setTemperature(pHumidity self, int16_t newTemperature){
	self->temperature = newTemperature;
}

uint16_t getHumidity(pHumidity self) {

	return self->humidity;
}

void setHumidity(pHumidity self, uint16_t newMeasure) {

	self->humidity = newMeasure;
}


void task_Humidity(void* pvParameters) {

	hih8120Wakeup();
	humidity_meassure(pvParameters);
	
	printf("Humidity task started \n");
	for (;;) {
		xEventGroupSetBits(xEventGroup, BIT_1);
		vTaskDelay(pdMS_TO_TICKS(4000));
		humidity_meassure(pvParameters);

	}
}

