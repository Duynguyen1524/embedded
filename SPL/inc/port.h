#ifndef PORT_H
#define PORT_H

#include <stdint.h>
#include "Std_types.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


#define PORT_ID_A   0   /* GPIOA */
#define PORT_ID_B   1   /* GPIOB */
#define PORT_ID_C   2   /* GPIOC */
#define PORT_ID_D   3   /* GPIOD */
#define PORT_PIN_MODE_DIO  0
#define PORT_PIN_MODE_ADC  1
#define PORT_PIN_MODE_PWM  2
#define PORT_PIN_MODE_UART 3
#define PORT_PIN_MODE_SPI  4
#define PORT_PIN_MODE_I2C  5
#define PORT_PIN_MODE_CAN  6
#define PORT_PIN_MODE_ETH  7
#define PORT_PIN_MODE_USB  8
#define PORT_GET_PIN_MASK(PinNum)   (1U << (PinNum))
 
#define PORT_GET_PORT(PortNum) \
    ((PortNum) == PORT_ID_A ? GPIOA : \
    (PortNum) == PORT_ID_B ? GPIOB : \
    (PortNum) == PORT_ID_C ? GPIOC : \
    (PortNum) == PORT_ID_D ? GPIOD : NULL)
#define PORT_GET_PIN_MASK(PinNum)   (1U << (PinNum))


#define PULL_UP  0
#define PULL_DOWN  1
#define NO_PULL  2

#define PORT_CHANGEABLE 1
#define PORT_NOT_CHANGEABLE 0





typedef uint8_t Port_PinType;
typedef enum{
    PORT_PIN_IN = 0,
    PORT_PIN_OUT,
} Port_PinDirectionType;
typedef uint8_t Port_PinModeType;

typedef enum {
    Pin_Speed_2MHz = 0,
    Pin_Speed_10MHz = 1,
    Pin_Speed_50MHz = 2,
} Port_PinSpeedType;


typedef struct 
{   uint8_t PortNum; // Port number (0=A, 1=B, 2=C, 3=D)
    uint8_t PinNum;  // Pin number (0-15)
    Port_PinModeType mode;
    Port_PinDirectionType direction;
    Port_PinSpeedType speed;
    uint8 level;
    uint8_t pull; // Pull-up or Pull-down configuration
    uint8_t alternate_function; // For alternate function modes
    uint8_t changeble; // Indicates if the pin can change its mode

} Port_PinConfigType;
typedef struct {
    const Port_PinConfigType* PinConfigs; /**< Pointer to array of pin configurations */
    uint16_t PinCount;                    /**< Number of configured pins */
} Port_ConfigType;

void Port_Init (const Port_ConfigType* ConfigPtr);
void Port_SetPinDirection (Port_PinType Pin,Port_PinDirectionType Direction);
void Port_RefreshPortDirection (void);
void Port_GetVersionInfo (Std_VersionInfoType* versioninfo);
void Port_SetPinMode (Port_PinType Pin,Port_PinModeType Mode);





#endif // PORT_H