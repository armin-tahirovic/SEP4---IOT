#include "temperature.h"

typedef struct temperature {
	int driverPort;
	uint16_t temp
}temperature_t;



int temperature_create() {
	pTemperature driverPort = (pTemperature)pvPortMalloc(sizeof(temperature_t));

	if (NULL == driverPort) {
		return NULL;
	}

	return driverPort;

}

void temperature_meassure(pTemperature self) {
	self->temp = rand() % 50;
}



uint16_t getTemperature(pTemperature self) {
	xSemaphoreTake(xSemaphore, portMAX_DELAY);
	return self->temp;
	xSemaphoreGive(xSemaphore);
}


void task_temperature(void* pvParameters) {
	(void)pvParameters;
	pTemperature data = pvParameters;
	for (;;) {
		xEventGroupSetBits(xEventGroup, BIT_1);
		vTaskDelay(pdMS_TO_TICKS(200));
		meassure(pvParameters);

	}
}

