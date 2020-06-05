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

			if ( hcSr501IsDetecting(motion_hcSr501Inst) )
			{
				printf("is detecting \n");
				self->activity = 1;
			}
			else
			{
				printf("is NOT detecting \n");
				self->activity = 0;
			}
		
		printf("activity: %d \n", self->activity);
	
}

uint8_t getActivity(pMOTION self) {

	return self->activity;
}

void setActivity(pMOTION self, uint8_t newActivity) {

	self->activity = newActivity;
}

void motion_setSensor(hcSr501_p inst){
	motion_hcSr501Inst = NULL;
}

void task_MOTION(void* pvParameters) {


	for (;;) {
		
		vTaskDelay(pdMS_TO_TICKS(61000));
		motion_meassure(pvParameters);
	}
}
