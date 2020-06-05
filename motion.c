
#include "motion.h"

typedef struct MOTION {
	uint8_t activity;
}MOTION_t;

pMOTION motion_create() {
	pMOTION driverPort = (pMOTION)pvPortMalloc(sizeof(MOTION_t));

	if (NULL == driverPort)
	return NULL;

	return driverPort;

}

void motion_destroy(pMOTION self) {
	vPortFree(self);
}



void motion_meassure(pMOTION self) {

		if ( hcSr501IsDetecting(hcSr501Inst) )
		{
			setActivity(self, 1);
		}
		else
		{
			setActivity(self, 0);
		}
		
		printf("activity: %d \n", self->activity);
	
}

uint8_t getActivity(pMOTION self) {

	return self->activity;
}

void setActivity(pMOTION self, uint8_t newActivity) {

	self->activity = newActivity;
}

void task_MOTION(void* pvParameters) {

	hcSr501Inst = hcSr501Create(&PORTE, PE5);

	for (;;) {
		
		vTaskDelay(pdMS_TO_TICKS(60000));
		motion_meassure(pvParameters);
	}
}
