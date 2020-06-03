#include "Room.h"

void taskRoomCollect(void* pvParameters) {
  (void)pvParameters;

  for (;;) {
    EventBits_t uxBits = xEventGroupWaitBits(xEventGroup, BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4, pdTRUE, pdTRUE, 500);
    if((uxBits & (BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4)) == (BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4)){
    vTaskDelay(pdMS_TO_TICKS(500));
    pLora loraWan = (pLora)pvPortMalloc(sizeof(LoraDriver_t));
    uint16_t co2 = getCO2(co2_sensor);

    loraWan->len = sizeof(uint16_t);
    loraWan->bytes = pvPortMalloc(sizeof(uint16_t));
    loraWan->bytes[0] = co2;
      
    printf("CO2: %i\n", co2_meassure);
    
    queue_lora(loraWan);
    xEventGroupClearBits(xEventGroup, BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4);
    }
  }
  vTaskDelete(NULL);
}
