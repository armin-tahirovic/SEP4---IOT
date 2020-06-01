#include "humidity.h"

typedef struct humidity {
	int driverPort;
	uint16_t humidity;
	int16_t temperature;
}humidity_t;



int humidity_create() {
	pHumidity driverPort = (pHumidity)pvPortMalloc(sizeof(humidity_t));

	if (NULL == driverPort) {
		return NULL;
	}

	return driverPort;

}

void humidity_meassure(pHumidity self) {
	hih8120Meassure();
}



uint16_t getHumidity(pHumidity self) {
	xSemaphoreTake(xSemaphore, portMAX_DELAY);
	return self->humidity;
	xSemaphoreGive(xSemaphore);
}

void setHumidity(pHumidity self, uint16_t newMeasure) {
	xSemaphoreTake(xSemaphore, portMAX_DELAY);
	self->humidity = newMeasure;
	xSemaphoreGive(xSemaphore);
}


void task_Humidity(void* pvParameters) {
	(void)pvParameters;
	pHumidity data = pvParameters;

	for (;;) {
		hih8120Wakeup();
		xEventGroupSetBits(xEventGroup, BIT_4);
		vTaskDelay(pdMS_TO_TICKS(1000));
		humidity_meassure(pvParameters);
		uint16_t newHumidity = hih8120GetHumidityPercent_x10();
		int16_t newTemperature = hih8120GetTemperature_x10();

		printf("From Humidity Class");
		printf("Humidity: %d and temperature: %d \n", newHumidity, newTemperature);

	}
}

