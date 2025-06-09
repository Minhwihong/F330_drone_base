#ifndef __PORT_STM32_ADC_H__
#define __PORT_STM32_ADC_H__
#if 0
#include "typeSimple.h"
#include "stm32f4xx_hal.h"

typedef struct {

    ADC_HandleTypeDef* pxHwAdc;

}HwAdcWrapper_t;


void portHw_InitAdcDrive(HwAdcWrapper_t* pxHwWrapper, ADC_HandleTypeDef* _pxHwAdc);
void portHw_StartAdc_dma(HwAdcWrapper_t* pxHwWrapper, u16* pusBuf);
u16 portHw_GetAdc_ChannelCnt(HwAdcWrapper_t* pxHwWrapper);
#endif

#endif
