#include "co2.h"

typedef struct CO2 {
	uint16_t co2;
}CO2_t;

pCO2 co2_create() {
	pCO2 driverPort = (pCO2)pvPortMalloc(sizeof(CO2_t));

	if (NULL == driverPort)
	return NULL;
	
	driverPort->co2 = 0;

	return driverPort;

}

void co2_destroy(pCO2 self) {
	vPortFree(self);
}


void co2_meassure(pCO2 self) {
	xSemaphoreTake(xSemaphore_co2, portMAX_DELAY);
	mh_z19_take_meassuring();
	xSemaphoreGive(xSemaphore_co2);
}

uint16_t getCO2(pCO2 self) {
	return self->co2;
}

void setCO2(pCO2 self, uint16_t co2ppm) {
	self->co2 = co2ppm;
}


void task_CO2(void* pvParameters) {
	printf("CO2 task started \n");
	for (;;) {
		xEventGroupSetBits(xEventGroup, BIT_0);
		vTaskDelay(pdMS_TO_TICKS(4500));
		
		co2_meassure(pvParameters);
			
	}
}
