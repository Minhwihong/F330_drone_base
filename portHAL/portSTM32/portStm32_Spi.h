#ifndef __PORT_STM32_SPI_H__
#define __PORT_STM32_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "typeSimple.h"
#include "stm32f4xx_hal.h"
#include "portStm32_Gpio.h"

typedef struct {
    SPI_HandleTypeDef* pxSpiHw;
    u32 uiSendDel;
    u32 uiRcvDel;
}SPI_HwWrapper;


void portHw_SpiInit(SPI_HwWrapper* pxSpi, SPI_HandleTypeDef* pxSpiHw, u32 _uiSendDel, u32 _uiRcvDel);


u8 portHw_readByte(SPI_HwWrapper* pxSpi,   u8* ucData);
u8 portHw_readBytes(SPI_HwWrapper* pxSpi,   u8* ucData, u16 len);

u8 portHw_writeByte(SPI_HwWrapper* pxSpi,   u8 ucData);
u8 portHw_writeBytes(SPI_HwWrapper* pxSpi,   u8* ucData, u16 len);


void portHw_chipSelect(Gpio_HwWrapper* pxCs, u8 onOff);

#ifdef __cplusplus
}
#endif

#endif