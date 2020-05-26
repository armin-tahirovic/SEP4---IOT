#include "humidity.h"

typedef struct humidity {
	int driverPort;
	uint16_t humidity
}humidity_t;



int humidity_create() {
	pHumidity driverPort = (pHumidity)pvPortMalloc(sizeof(humidity_t));

	if (NULL == driverPort) {
		return NULL;
	}

	return driverPort;

}

void humidity_meassure(pHumidity self) {
	self->humidity = rand() % 50;
}



uint16_t getHumidity(pHumidity self) {

	return self->humidity;
}


void task_humidity(void* pvParameters) {
	(void)pvParameters;
		pHumidity data = pvParameters;

		uint16_t getHumidity(pHumidity self); 
			for (;;) {
				vTaskDelay(pdMS_TO_TICKS(200));
				meassure(pvParameters);

			}
		}



