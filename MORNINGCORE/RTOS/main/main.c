#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "dht11.h"

SemaphoreHandle_t dht11_mutex;

void taskA(void* param)
{
    // give semaphore
    int temp, humidity;

    while(1)
    {
        xSemaphoreTake(dht11_mutex, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(500));
        if(DHT11_StartGet(&temp, &humidity))
        {
            ESP_LOGI("dht11","taskA-->temp:%d, humidity:%d%%",temp/10,humidity);
        }
        xSemaphoreGive(dht11_mutex);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void taskB(void* param)
{
    // take semaphore
    int temp, humidity;

    while(1)
    {
        xSemaphoreTake(dht11_mutex, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(500));
        if(DHT11_StartGet(&temp, &humidity))
        {
            ESP_LOGI("dht11","taskB-->temp:%d, humidity:%d%%",temp/10,humidity);
        }
        xSemaphoreGive(dht11_mutex);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void app_main(void)
{
    
    dht11_mutex = xSemaphoreCreateMutex();
    DHT11_Init(GPIO_NUM_4);
    xTaskCreatePinnedToCore(taskA, "taskA", 2048, NULL, 3, NULL, tskNO_AFFINITY);
    xTaskCreatePinnedToCore(taskB, "taskB", 2048, NULL, 4, NULL, tskNO_AFFINITY);
}
