#include "Std_types.h"
#include "dio.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include <stddef.h>

GPIO_TypeDef* Get_port(uint8_t PortId) {
    Dio_PortType port =  PortId;      // Assuming max 15 pins per port
    GPIO_TypeDef *GPIOx = NULL;

    switch (port) {
        case 0: GPIOx = GPIOA; break;
        case 1: GPIOx = GPIOB; break;
        case 2: GPIOx = GPIOC; break;
        case 3: GPIOx = GPIOD; break;
        case 4: GPIOx = GPIOE; break;
        case 5: GPIOx = GPIOF; break;
        case 6: GPIOx = GPIOG; break;
        default: GPIOx = NULL; break; // Invalid port
    }

    return GPIOx;
}
Dio_ChannelType Get_channel(Dio_ChannelType ChannelId){
    return (ChannelId % 15); // Assuming max 15 pins per port
}
