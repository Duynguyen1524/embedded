
#ifndef DIO_H
#define DIO_H


#include <stdint.h>
#include <stdbool.h>

typedef int8_t Dio_ChannelType;
typedef uint8_t Dio_PortType;
struct   Dio_ChannelGroupType{
    Dio_PortType port;
    uint8_t mask;
    uint8_t offset;
} Dio_ChannelGroupType;

typedef uint8_t Dio_LevelType;  
typedef uint8_t Dio_PortLevelType;
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId);
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level);

#endif // DIO_H