#include "Room.h"

typedef struct Room
{
  char* name;
  uint8_t threshold;
} Room_t;

pRoom room_create() {
  pRoom new_Room = (pRoom)pvPortMalloc(sizeof(Room_t));

  if (new_Room == NULL)
    return NULL;

  return new_Room;
}

void room_destroy(pRoom self) {
  vPortFree(self);
}

void taskRoomCollect(void* pvParameters) {
  (void)pvParameters;

  for (;;) {
    vTaskDelay(pdMS_TO_TICKS(500));
    int co2_meassure = getCO2(co2_sensor);

    printf("CO2: %i\n", co2_meassure);
  }
}
