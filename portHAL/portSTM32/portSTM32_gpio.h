#ifndef __PORT_STM32_GPIO_H__
#define __PORT_STM32_GPIO_H__

extern "C" {
#include "stm32f4xx_hal.h"
#include "string.h"
}

#include "typeSimple.h"
#include "IGpio.h"


class portSTM32Gpio : public IGpio {

public:
    portSTM32Gpio(eGpioMode _mode, u8 _m_ucUseFilter, GPIO_TypeDef * _pstGpioPort, uint16_t _usGpioPin) : 
    	IGpio(_m_ucUseFilter, _mode), m_pstGpioPort(_pstGpioPort), m_usGpioPin(_usGpioPin) {
        //m_ucUseFilter = _m_ucUseFilter;
        //m_useMode = _mode;

//        m_pstGpioPort = _pstGpioPort;
//        m_usGpioPin = _usGpioPin;

        //IGpio::Init(_mode, _m_ucUseFilter);
    }

    void Init(eGpioMode _mode, GPIO_TypeDef * _pstGpioPort, uint16_t _usGpioPin){
        m_pstGpioPort = _pstGpioPort;
        m_usGpioPin = _usGpioPin;

        (void)_mode;
        //IGpio::Init(_mode);
    }

    void Toggle() override {
        HAL_GPIO_TogglePin(m_pstGpioPort, m_usGpioPin);
    }

    void Write(bool sig) override {
        HAL_GPIO_WritePin(m_pstGpioPort, m_usGpioPin, (sig == true) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    u8 Read() override {
        return HAL_GPIO_ReadPin(m_pstGpioPort, m_usGpioPin) == GPIO_PIN_SET;
    }

private:
    GPIO_TypeDef * m_pstGpioPort;
	uint16_t m_usGpioPin;
};




#endif
