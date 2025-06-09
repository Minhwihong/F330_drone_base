#ifndef __IUART_H__
#define __IUART_H__

//#include <iostream>
#include <functional>
#include <optional>

#include "typeSimple.h"
#include "byteQueue.h"

enum class eUartRcvMode{
    DMA_BUF_LINEAR,
    DMA_BUF_CIRCULAR,
    BUF_CIRCULAR,
    BUF_LINEAR
};


enum class eUartCbType{
    None = 0,
    RcvDone,
    RcvIdleDetect,
    RcvDMADone,
    TxDone,
    Max,
};


// UART 인터페이스 정의
class UartInterface {
public:

    virtual uint8_t OpenPort(eUartRcvMode mode) = 0;

    virtual uint8_t ResetRcv() = 0;

    virtual u8 SendDataDMA(u8* data, u16 len) = 0;

    

    virtual bool ReadByteInQue(u8* ch) = 0;

    virtual bool IsDataAvailable() = 0;

    virtual u8 GetPortStatus() = 0;

    virtual void SetRcvQueuePtr(QueLinear* queLinear, QueDMACircular* queCircle, uint32_t* addr) = 0;

    /* *********************************** Interrupt Handling *********************************** */
    virtual void RegisterRcvCallback(eUartCbType type, void(*callback)(void*), void* param) = 0;

    virtual void OnISR_RcvIdleDetect(u16 size) = 0;
    virtual void OnISR_TxDone() = 0;



    virtual ~UartInterface() = default;
};


class UartContext {
private:
    UartInterface* uart;

public:
    UartContext(UartInterface* uartImpl) : uart(uartImpl) {}

    void OpenPort(eUartRcvMode baudRate) {
        uart->OpenPort(baudRate);
    }

    void write(const char* data) {
        //uart->write(data);

        (void)data;
    }


    void WriteDMA(u8* data, u16 len){
        uart->SendDataDMA(data, len);
    }

    void RegisterReadCallback(eUartCbType type, void(*callback)(void*), void* param) {
        uart->RegisterRcvCallback(type, callback, param);
    }
};

#endif
