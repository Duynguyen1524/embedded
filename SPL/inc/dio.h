
#ifndef DIO_H
#define DIO_H


#include <stdint.h>
#include <stdbool.h>

typedef int8_t Dio_ChannelType;
typedef uint8_t Dio_PortType;
typedef struct {
    Dio_PortType port;  // The GPIO port (e.g., GPIOA, GPIOB, etc.)
    uint8_t mask;       // Mask of the group bits
    uint8_t offset;     // Offset of the group within the port
} Dio_ChannelGroupType;

typedef uint8_t Dio_LevelType;  
typedef uint8_t Dio_PortLevelType;
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId);
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level);
void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level);
Dio_PortLevelType Dio_ReadChannelGroup (const  Dio_ChannelGroupType* ChannelGroupIdPtr);
void Dio_WriteChannelGroup (const  Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId);

#endif // DIO_H