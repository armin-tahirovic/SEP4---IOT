#include "co2.h"
#include <mh_z19.h>

typedef struct CO2 {
	uint16_t driverPort;
	uint16_t co2;
}CO2_t;

uint16_t co2_create() {
	pCO2 driverPort = (pCO2)pvPortMalloc(sizeof(CO2_t));

	if (NULL == driverPort)
	return NULL;

	return driverPort;

}

void co2_destroy(pCO2 self) {
	vPortFree(self);
}



void co2_meassure(pCO2 self) {

			mh_z19_take_meassuring();
			PORTA ^= _BV(PA7);
	
}

uint16_t getCO2(pCO2 self) {

	return self->co2;
}

void setCO2(pCO2 self, uint16_t ppm) {

	self->co2 = ppm;
}

void task_CO2(void* pvParameters) {
	(void)pvParameters;


	for (;;) {
	
		vTaskDelay(pdMS_TO_TICKS(1500));
		co2_meassure(co2_sensor);
	}
}
