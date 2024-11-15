#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

void taskA(void* param)
{   

    //

    while(1)
    {

    }
}

void taskB(void* param)
{
    //

    while(1)
    {

    }
}


void app_main(void)
{

    xTaskCreatePinnedToCore(taskA, "taskA", 2048, NULL, 3, NULL, tskNO_AFFINITY);
    xTaskCreatePinnedToCore(taskB, "taskB", 2048, NULL, 3, NULL, tskNO_AFFINITY);
}
