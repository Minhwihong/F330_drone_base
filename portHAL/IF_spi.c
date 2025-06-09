#include "IF_spi.h"



u8 InitSpiHardware(ISpi* pxISpi, SPI_HwWrapper* pxSpiHw, GpioNode_t* pxGpoCs){

    if(pxSpiHw == (void*)0 || pxGpoCs == (void*)0){
        return 1;
    }

    pxISpi->pxSpiHw = pxSpiHw;
    pxISpi->pxGpo_Cs = pxGpoCs;

    WriteGpio(pxGpoCs, 1);

    return 0;
}


u8 ISpiReadByte(ISpi* pxSpi, u8* ucData){

    u8 rtn = 0;

    rtn = portHw_readByte(pxSpi->pxSpiHw,  ucData);

    return rtn;
}


u8 ISpiReadBytes(ISpi* pxSpi, u8* ucData, u16 len){

    u8 rtn = 0;

    rtn = portHw_readBytes(pxSpi->pxSpiHw, ucData, len);

    return rtn;
}



u8 ISpiWriteByte(ISpi* pxSpi, u8 ucData){

    u8 rtn = 0;

    rtn = portHw_writeByte(pxSpi->pxSpiHw,  ucData);

    return rtn;
}


u8 ISpiWriteBytes(ISpi* pxSpi, u8* ucData, u16 len){

    u8 rtn = 0;

    rtn = portHw_writeBytes(pxSpi->pxSpiHw,  ucData, len);

    return rtn;
}

void ISpiChipSelect(ISpi* pxSpi, u8 onOff){

    portHw_chipSelect(pxSpi->pxGpo_Cs->pxGpioPin, onOff);

}