#include "entry.h"

void TaskBoardLedCtl(void* args);
void TaskBasic(void* args);

void EntryPoint(){

    static xTaskHandle xTskHnd_basic;
    static xTaskHandle xTskHnd_boardLed;

    xTaskCreate(TaskBasic, "Basic", 128, (void*)0, 2, &xTskHnd_basic);
    xTaskCreate(TaskBoardLedCtl, "ctl_led", 128, (void*)0, 2, &xTskHnd_boardLed);
}



void TaskBasic(void* args){

    (void)args;

    while(1){

        vTaskDelay(100);
    }

}



void TaskBoardLedCtl(void* args){

    (void)args;

    while(1){

        //HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
        HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);

        vTaskDelay(1000);

    }

}



void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
    /* If the buffers to be provided to the Idle task are declared inside this
       function then they must be declared static - otherwise they will be allocated on
       the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
       state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
       Note that, as the array is necessarily of type StackType_t,
       configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}