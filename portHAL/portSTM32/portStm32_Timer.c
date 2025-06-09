#include "portStm32_Timer.h"
#include "IF_timer.h"

extern TimerContainer_t* g_pxTmContainerMain ;




void portHw_StartHWTimer(Tm_HwWrapper* pxHwTimer){

    TIM_HandleTypeDef* pxSTTimer = pxHwTimer->pxTimer;

    HAL_TIM_Base_Start_IT(pxSTTimer);
}


void portHw_StopHWTimer(Tm_HwWrapper* pxHwTimer){

    TIM_HandleTypeDef* pxSTTimer = pxHwTimer->pxTimer;

    HAL_TIM_Base_Stop_IT(pxSTTimer);
}




void portHw_InitCountingTimer(Tm_HwWrapper* pxTimer){

    TIM_HandleTypeDef* pxSTTimer = pxTimer->pxTimer;

    (void)pxSTTimer;

}


u32 portHw_GetTimerCount(Tm_HwWrapper* pxTimer){

    TIM_HandleTypeDef* pxSTTimer = pxTimer->pxTimer;

    return __HAL_TIM_GET_COUNTER(pxSTTimer);
}


void portHw_ResetTimerCount(Tm_HwWrapper* pxTimer){

    TIM_HandleTypeDef* pxSTTimer = pxTimer->pxTimer;
    __HAL_TIM_SET_COUNTER(pxSTTimer, 0);
}









// Stm32 Timer Period Elapsed Callback
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */

  /* USER CODE BEGIN Callback 1 */
  if( htim->Instance == TIM7 ) {

    HWTimerCallback(g_pxTmContainerMain);
  }
  /* USER CODE END Callback 1 */
}
