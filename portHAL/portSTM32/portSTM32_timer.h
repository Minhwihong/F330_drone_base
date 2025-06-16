#ifndef __PORT_STM32_TIMER_H__
#define __PORT_STM32_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "typeSimple.h"
#include "stm32f4xx_hal.h"


typedef struct {
    TIM_HandleTypeDef* pxTimer;
}Tm_HwWrapper;



void portHw_StopHWTimer(Tm_HwWrapper* pxHwTimer);
void portHw_StartHWTimer(Tm_HwWrapper* pxHwTimer);
//void OnTimerPeriodExpired(Tm_HwWrapper* pxHwTimer);


void portHw_InitCountingTimer(Tm_HwWrapper* pxTimer);
u32 portHw_GetTimerCount(Tm_HwWrapper* pxTimer);
void portHw_ResetTimerCount(Tm_HwWrapper* pxTimer);

#ifdef __cplusplus
}
#endif

#endif
