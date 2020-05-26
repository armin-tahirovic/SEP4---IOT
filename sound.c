#include "sound.h"

typedef struct sound {
	int driverPort;
	uint16_t sound
}sound_t;



int sound_create() {
	pSound driverPort = (pSound)pvPortMalloc(sizeof(sound_t));

	if (NULL == driverPort) {
		return NULL;
	}

	return driverPort;

}

void sound_meassure(pSound self) {
	self->sound = rand() % 50;
}



uint16_t getSound(pSound self) {

	return self->sound;
}


void task_sound(void* pvParameters) {
	(void)pvParameters;
	pSound data = pvParameters;
	for (;;) {
		vTaskDelay(pdMS_TO_TICKS(200));
		meassure(pvParameters);

	}
}


