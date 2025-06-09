#ifndef __IF_SPI_H__
#define __IF_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "portStm32_Spi.h"
#include "IF_gpio.h"

typedef struct {
    SPI_HwWrapper* pxSpiHw;
    GpioNode_t* pxGpo_Cs;
}ISpi;




u8 InitSpiHardware(ISpi* pxISpi, SPI_HwWrapper* pxSpiHw, GpioNode_t* pxGpoCs);

u8 ISpiReadByte(ISpi* pxSpi, u8* ucData);
u8 ISpiReadBytes(ISpi* pxSpi, u8* ucData, u16 len);

u8 ISpiWriteByte(ISpi* pxSpi, u8 ucData);
u8 ISpiWriteBytes(ISpi* pxSpi, u8* ucData, u16 len);

void ISpiChipSelect(ISpi* pxSpi, u8 onOff);

#ifdef __cplusplus
}
#endif

#endif