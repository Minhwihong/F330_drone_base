#include "portStm32_Adc.h"

#if 0
void portHw_InitAdcDrive(HwAdcWrapper_t* pxHwWrapper, ADC_HandleTypeDef* _pxHwAdc){

    pxHwWrapper->pxHwAdc = _pxHwAdc;

}


void portHw_StartAdc_dma(HwAdcWrapper_t* pxHwWrapper, u16* pusBuf){

    u16 usChCnt = 0;

    usChCnt = portHw_GetAdc_ChannelCnt(pxHwWrapper);

    HAL_ADC_Start_DMA(pxHwWrapper->pxHwAdc, (uint32_t *)pusBuf, usChCnt);

}



u16 portHw_GetAdc_ChannelCnt(HwAdcWrapper_t* pxHwWrapper){

    u16 rtn = 0;

    rtn = pxHwWrapper->pxHwAdc->Init.NbrOfConversion;

    return rtn;
}
#endif
