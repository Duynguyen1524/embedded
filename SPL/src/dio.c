#include "dio.h"
#include <stdint.h>
#include <stdbool.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "Std_Types.h"
#include <stddef.h>

Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId){
    GPIO_TypeDef* GPIOx =  GET_PORT(ChannelId); // Assuming max 16 pins per port
    Dio_ChannelType channel = GET_CHANNEL(ChannelId); 
    if(GPIOx == NULL) {
        return DIO_LOW; // Invalid port
    }
    if( GPIO_ReadInputDataBit(GPIOx, (1 << channel)) == Bit_SET){
        return DIO_HIGH; // DIO_HIGH
    } else {
        return DIO_LOW; // DIO_LOW
    }

}


void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level){
    GPIO_TypeDef* GPIOx =  GET_PORT(ChannelId); // Assuming max 16 pins per port
    Dio_ChannelType channel = GET_CHANNEL(ChannelId); // Assuming max 16 pins per port
    if(GPIOx == NULL) {
        return; // Invalid port
    }
    if(Level == DIO_HIGH){
        GPIO_SetBits(GPIOx, (1 << channel));
    } else {
        GPIO_ResetBits(GPIOx, (1 << channel));
    }
}

Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId){

    GPIO_TypeDef* GPIOx = GET_PORT(PortId); // Get the GPIO port based on PortId
    return (Dio_PortLevelType)GPIO_ReadInputData(GPIOx);
}
void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level){
    GPIO_TypeDef* GPIOx = GET_PORT(PortId); // Get the GPIO port based on PortId
    
    GPIO_Write(GPIOx, Level);
}


Dio_PortLevelType Dio_ReadChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr){
    GPIO_TypeDef* GPIOx = GET_PORT(ChannelGroupIdPtr->port); // Get the GPIO port based on ChannelGroupIdPtr
    if(GPIOx == NULL) {
        return 0; // Invalid port
    }
    uint16_t mask = ChannelGroupIdPtr->mask;
    uint16_t offset = ChannelGroupIdPtr->offset;
    uint16_t portValue = GPIO_ReadInputData(GPIOx);
    return (Dio_PortLevelType)((portValue >> offset) & mask);
   

}
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level){
    GPIO_TypeDef* GPIOx = GET_PORT(ChannelGroupIdPtr->port); // Get the GPIO port based on ChannelGroupIdPtr
    if(GPIOx == NULL) {
        return; // Invalid port
    }
    uint16_t mask = ChannelGroupIdPtr->mask;
    uint16_t offset = ChannelGroupIdPtr->offset;
    uint16_t portValue = (Level & mask) << offset;
    GPIO_Write(GPIOx, portValue);
}
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId){
    GPIO_TypeDef* GPIOx =  GET_PORT(ChannelId); // Assuming max 16 pins per port
    Dio_ChannelType channel = GET_CHANNEL(ChannelId); // Assuming max 16 pins per port
    
    if(GPIO_ReadInputDataBit(GPIOx, (1 << channel)) == Bit_SET){
        GPIO_ResetBits(GPIOx, (1 << channel));
        return DIO_LOW; // DIO_LOW
    } else {
        GPIO_SetBits(GPIOx, (1 << channel));
        return DIO_HIGH; // DIO_HIGH
    }
}


