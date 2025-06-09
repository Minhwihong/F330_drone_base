#include "board_stm32f429disc.h"
#include "main.h"
#include "IF_Hal.h"




u32 g_uiTTL = 0;
ISpi* g_pxComm_Icm20602;
GpioNode_t g_xGpo_Icm20602_cs;



extern GpioNode_t g_xGpo_boardLed1;
extern GpioNode_t g_xGpo_boardLed2;

extern TimerContainer_t g_xTmContainer;
extern TimerCounter_t g_xTmCounter;

static u16 g_usGpioId = 0;



static void InitTimerTask_TTL();
static void TimerTask_TTL(void* args);





void BSP_BaseTimerInit(){

  static Tm_HwWrapper basicTimer;

  basicTimer.pxTimer = &htim7;


  InitTimer(&g_xTmContainer, &basicTimer);


  InitTimerTask_TTL();


  // Start Timer
  TimerContainerCtl(&g_xTmContainer, 1);
}






void BSP_BoardLedInit(){

    static Gpio_HwWrapper xGpo_boardLed1 = {LD3_GPIO_Port, LD3_Pin };
    static Gpio_HwWrapper xGpo_boardLed2 = {LD4_GPIO_Port, LD4_Pin };


    GpioPin_Def(g_usGpioId++, GPIO_PIN_OUT, GPI_FILTER_OFF, &g_xGpo_boardLed1, &xGpo_boardLed1);
    GpioPin_Def(g_usGpioId++, GPIO_PIN_OUT, GPI_FILTER_OFF, &g_xGpo_boardLed2, &xGpo_boardLed2);

}




void BSP_Icm20602Init(){

  static ISpi xComm_Icm20602;
  static SPI_HwWrapper xSpi_Icm20602;
  static Gpio_HwWrapper xSpiCs_Icm20602;

  portHw_SpiInit(&xSpi_Icm20602, &hspi2, 1000, 1000);
  GpioPin_Def(g_usGpioId++, GPIO_PIN_OUT, GPI_FILTER_OFF, &g_xGpo_Icm20602_cs, &xSpiCs_Icm20602);


  InitSpiHardware(&xComm_Icm20602, &xSpi_Icm20602, &g_xGpo_Icm20602_cs);

  g_pxComm_Icm20602 = &xComm_Icm20602;
}






















static void InitTimerTask_TTL(){

  static TimerTask_t xTmTask1;

	xTmTask1 = CreateTimerTask(TimerTask_TTL, (void*)0, 100, HARD_TIMER_STARTED);
	RegisterTimer(&g_xTmContainer, &xTmTask1);
}





static void TimerTask_TTL(void* args){
	
  (void)args;

  g_uiTTL++;
}






#if 0
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

  if(htim == &htim7){

    //HAL_GPIO_WritePin(SPI1_RST_GPIO_Port, SPI1_RST_Pin, GPIO_PIN_SET );
    //g_glbHwTimer.HWTimerCallback();
    //HAL_GPIO_WritePin(SPI1_RST_GPIO_Port, SPI1_RST_Pin, GPIO_PIN_RESET );
    
  }
}
#endif