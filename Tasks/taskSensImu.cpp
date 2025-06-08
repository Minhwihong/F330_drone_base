#include "taskSensImu.h"
#include "ICM20602.h"
#include "tiny_printf.h"

int16_t g_ausGyro[3] = {0,};

void TaskSenseIMU(void* args){

    (void)args;

    while(true){

        ICM20602_Get3AxisGyroRawData(g_ausGyro);
        printf("X: %d, Y: %d, Z: %d\r\n",g_ausGyro[0], g_ausGyro[1],g_ausGyro[2] );

        vTaskDelay(10);
    }

}