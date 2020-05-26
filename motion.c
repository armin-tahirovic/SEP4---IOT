#include "motion.h"

typedef struct motion {
	int driverPort;
	uint16_t motion
}motion_t;



int motion_create() {
	pMotion driverPort = (pMotion)pvPortMalloc(sizeof(motion_t));

	if (NULL == driverPort) {
		return NULL;
	}

	return driverPort;

}

void motion_meassure(pMotion self) {
	self->motion = rand() % 50;
}



uint16_t getMotion(pMotion self) {

	return self->motion;
}


void task_motion(void* pvParameters) {
	(void)pvParameters;
	pMotion data = pvParameters;
	for (;;) {
		vTaskDelay(pdMS_TO_TICKS(200));
		meassure(pvParameters);

	}
}


