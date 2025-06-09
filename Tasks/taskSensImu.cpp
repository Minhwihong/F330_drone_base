#include "taskSensImu.h"
#include "ICM20602.h"
#include "tiny_printf.h"

int16_t g_ausGyro[3] = {0,};
extern ISpi* g_pxComm_Icm20602;

void TaskSenseIMU(void* args){

    (void)args;

    ICM20602_Initialization(g_pxComm_Icm20602);

    while(true){

        ICM20602_Get3AxisGyroRawData(g_pxComm_Icm20602, g_ausGyro);
        printf("X: %d, Y: %d, Z: %d\r\n",g_ausGyro[0], g_ausGyro[1],g_ausGyro[2] );

        vTaskDelay(10);
    }

}