#include "Port.h"
#include "dio.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "Std_types.h"
#include <stddef.h>
#include "Portconfig.h"

static uint8_t Port_Initialized = 0;
static void Port_ApplyPinConfig(const const Port_PinConfigType* pinCfg){
        GPIO_InitTypeDef GPIO_InitStruct;
        uint16 pinMask = PORT_GET_PIN_MASK(pinCfg->PinNum);
    switch (pinCfg->PortNum)  // Assuming max 16 pins per port
    {
    case 0:
        /* code */
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        break;
    case 1:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        break;
    case 2:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        break;
    case 3:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
        break;
    case 4:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
        break;
    default:
        break;
    }
        GPIO_InitStruct.GPIO_Pin = pinMask; // Set the pin mask

        
        if(pinCfg->speed == Pin_Speed_2MHz) {
            GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; // 2 MHz speed
        } else if (pinCfg->speed == Pin_Speed_10MHz) {
            GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz; // 10 MHz speed
        } else {
            GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // 50 MHz speed
        }
        if(pinCfg->mode == PORT_PIN_MODE_DIO){
            if(pinCfg->direction == PORT_PIN_OUT){
                if(pinCfg->pull  < NO_PULL) {
                    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
                } else {
                    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD; // Open-drain output
                } 
                
            } else {
                if(pinCfg->pull == PULL_UP) {
                    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // Pull-up input
                } else if(pinCfg->pull == PULL_DOWN) {
                    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; // Pull-down input
                } else {
                    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // No pull-up or pull-down
                }
            }

        }
        switch (pinCfg->pin / 16) // Assuming max 16 pins per port
        {
        case 0:
            GPIO_Init(GPIOA, &GPIO_InitStruct);
            break;
        case 1:
            GPIO_Init(GPIOB, &GPIO_InitStruct);
            break;
        case 2:
            GPIO_Init(GPIOC, &GPIO_InitStruct);
            break;
        case 3:
            GPIO_Init(GPIOD, &GPIO_InitStruct);
            break;
        default:
            break;
        }
       
        
        if (pinCfg->direction == PORT_PIN_OUT) {
            if (pinCfg->level == PORT_PIN_LEVEL_HIGH)
                GPIO_SetBits(PORT_GET_PORT(pinCfg->PortNum), pinMask);
            else
                GPIO_ResetBits(PORT_GET_PORT(pinCfg->PortNum), pinMask);
        }
}
void Port_Init (const Port_ConfigType* ConfigPtr){
    
    if (ConfigPtr == NULL) return;

    for (uint16_t i = 0; i < ConfigPtr->PinCount; i++) {
        Port_ApplyPinConfig(&ConfigPtr->PinConfigs[i]);
    }
        // Initialize the GPIO port according to the configuration
                Port_Initialized = 1; // Mark as initialized
        return;

        
    
}


void Port_SetPinDirection (Port_PinType Pin,Port_PinDirectionType Direction){
    if(!Port_Initialized) return;
    if(Pin >= PortCfg_PinsCount) return; // Invalid pin number
    if (!PortCfg_Pins[Pin].changeble) return;

    Port_PinConfigType* pinCfg = (Port_PinConfigType*)&PortCfg_Pins[Pin]; // cast bỏ const để update runtime (nếu cần)
    pinCfg->direction = Direction;
    Port_ApplyPinConfig(pinCfg);


    

}
void Port_RefreshPortDirection (void){
    if(!Port_Initialized) return;
    for (uint16_t i = 0; i < PortCfg_PinsCount; i++) {
        if (!PortCfg_Pins[i].changeble) {
            Port_ApplyPinConfig(&PortCfg_Pins[i]);
        }
    }
}
void Port_GetVersionInfo (Std_VersionInfoType* versioninfo){
    if(versioninfo != NULL_PTR) {
        versioninfo->vendorID = 0x1234;  // Example vendor ID
        versioninfo->moduleID = 0x5678;  // Example module ID
        versioninfo->sw_major_version = 1;  // Example major version
        versioninfo->sw_minor_version = 0;  // Example minor version
        versioninfo->sw_patch_version = 0;  // Example patch version
    }
}
void Port_SetPinMode (Port_PinType Pin,Port_PinModeType Mode){
    if(!Port_Initialized) return;
    if(Pin >= PortCfg_PinsCount) return; // Invalid pin number
    if (!PortCfg_Pins[Pin].changeble) return;

    Port_PinConfigType* pinCfg = (Port_PinConfigType*)&PortCfg_Pins[Pin]; // cast bỏ const để update runtime (nếu cần)
    pinCfg->mode = Mode;
    Port_ApplyPinConfig(pinCfg);
    
}