#include "portStm32_Spi.h"



void portHw_SpiInit(SPI_HwWrapper* pxSpi,   SPI_HandleTypeDef* pxSpiHw, u32 _uiSendDel, u32 _uiRcvDel){

    pxSpi->pxSpiHw = pxSpiHw;
    pxSpi->uiRcvDel = _uiRcvDel;
    pxSpi->uiSendDel = _uiSendDel;
}



u8 portHw_readByte(SPI_HwWrapper* pxSpi,   u8* ucData){

    HAL_StatusTypeDef rtn = 0;

    //portHw_writePin(pxCs, 0);
    rtn = HAL_SPI_Receive(pxSpi->pxSpiHw, ucData, 1, pxSpi->uiSendDel);
    //portHw_writePin(pxCs, 1);

    if(rtn != 0){
        return 1;
    }
    else {
        return rtn;
    }
}



u8 portHw_readBytes(SPI_HwWrapper* pxSpi,   u8* ucData, u16 len){

    HAL_StatusTypeDef rtn = 0;

    //portHw_writePin(pxCs, 0);
    rtn = HAL_SPI_Receive(pxSpi->pxSpiHw, ucData, len, pxSpi->uiSendDel);
    //portHw_writePin(pxCs, 1);

    if(rtn != 0){
        return 1;
    }
    else {
        return rtn;
    }
}


u8 portHw_writeByte(SPI_HwWrapper* pxSpi,  u8 ucData){

    HAL_StatusTypeDef rtn = 0;

    //portHw_writePin(pxCs, 0);
    rtn = HAL_SPI_Transmit(pxSpi->pxSpiHw, &ucData, 1, pxSpi->uiSendDel);
    //portHw_writePin(pxCs, 1);

    if(rtn != 0){
        return 1;
    }
    else {
        return rtn;
    }
}

u8 portHw_writeBytes(SPI_HwWrapper* pxSpi,  u8* ucData, u16 len){

    HAL_StatusTypeDef rtn = 0;
    u16 cnt = 0;

    //portHw_writePin(pxCs, 0);
    rtn = HAL_SPI_Transmit(pxSpi->pxSpiHw, ucData, len, pxSpi->uiSendDel);
    //portHw_writePin(pxCs, 1);
    // while(cnt < len)
	// {
    //     HAL_SPI_Transmit(pxSpi->pxSpiHw, ucData[cnt++], 1, pxSpi->uiSendDel);
	// 	SPI1_SendByte(ucData[cnt++]); //Send Data to write
	// }



    if(rtn != 0){
        return 1;
    }
    else {
        return rtn;
    }
}


void portHw_chipSelect(Gpio_HwWrapper* pxCs, u8 onOff){

    if(onOff != 0){
        portHw_writePin(pxCs, 1);
    }
    else {
        portHw_writePin(pxCs, 0);
    }
}