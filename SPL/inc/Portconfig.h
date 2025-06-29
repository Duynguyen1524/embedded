#ifndef PORT_CONFIG_H
#define PORT_CONFIG_H
#define PortCfg_PinsCount 256 // Define the number of pins in the port
#include "Std_types.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "dio.h"
#include "port.h"



extern const Port_PinConfigType PortCfg_Pins[PortCfg_PinsCount];




#endif /* PORT_CONFIG_H */