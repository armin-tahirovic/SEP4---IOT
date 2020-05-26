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

	return self->temp;
}


void task_temperature(void* pvParameters) {
	(void)pvParameters;
	pTemperature data = pvParameters;
	for (;;) {
		vTaskDelay(pdMS_TO_TICKS(200));
		meassure(pvParameters);

	}
}


