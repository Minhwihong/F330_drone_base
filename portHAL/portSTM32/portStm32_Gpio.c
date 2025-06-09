#include "portStm32_Gpio.h"
#include "IF_gpio.h"

void portHw_GpioDef( GPIO_TypeDef* uiPort, u16 usPin, u8 ucMode, u8 ucUseFilter){

    (void)uiPort;
    (void)usPin;
    (void)ucMode;
    (void)ucUseFilter;

}


u8 portHw_readPin(Gpio_HwWrapper* pxPin){

    return HAL_GPIO_ReadPin(pxPin->uiPort, pxPin->usPin);
}


void portHw_writePin(Gpio_HwWrapper* pxPin, u8 l_ucPinState){

    HAL_GPIO_WritePin(pxPin->uiPort, pxPin->usPin, l_ucPinState );
}


void portHw_togglePin(Gpio_HwWrapper* pxPin){

    HAL_GPIO_TogglePin(pxPin->uiPort, pxPin->usPin);
    

}


void portHw_OnGpio_EdgeIsr_Callback(u16 usPin){

    OnGpio_EdgeIsr_Callback(usPin);
    
}



// Stm32 GPIO External Interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

  //portHw_OnGpio_EdgeIsr_Callback(GPIO_Pin);
  OnGpio_EdgeIsr_Callback(GPIO_Pin);
}