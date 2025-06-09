#include "board_stm32f429disc.h"
#include "main.h"



portSTM32Timer g_portTm6;
ITimer& g_glbHwTimer = g_portTm6;




static portSTM32Gpio g_portStm32_GPO_BdLed1(eGpioMode::Output, GPI_FILTER_OFF, LD3_GPIO_Port, LD3_Pin);
static portSTM32Gpio g_portStm32_GPO_BdLed2(eGpioMode::Output, GPI_FILTER_OFF, LD4_GPIO_Port, LD4_Pin);

extern IGpio* g_pxGpo_boardLed1;
extern IGpio* g_pxGpo_boardLed2;




void BSP_BaseTimerInit(){

    g_portTm6.GetTimerInstace(&htim7);
    IGpio::InitFilterConfig(&g_glbHwTimer);
}




void BSP_BoardLedInit(){

    static IGpio& xGpo_boardLed1 = g_portStm32_GPO_BdLed1;
    static IGpio& xGpo_boardLed2 = g_portStm32_GPO_BdLed2;

    g_pxGpo_boardLed1 = &xGpo_boardLed1;
    g_pxGpo_boardLed2 = &xGpo_boardLed2;

}















void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

  if(htim == &htim7){

    //HAL_GPIO_WritePin(SPI1_RST_GPIO_Port, SPI1_RST_Pin, GPIO_PIN_SET );
    g_glbHwTimer.HWTimerCallback();
    //HAL_GPIO_WritePin(SPI1_RST_GPIO_Port, SPI1_RST_Pin, GPIO_PIN_RESET );
    
  }
}