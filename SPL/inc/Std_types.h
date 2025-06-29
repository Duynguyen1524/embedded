#ifndef STD_TYPE_H
#define STD_TYPE_H


#include <stdint.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "dio.h"
#define uint8 uint8_t
#define uint16 uint16_t
#define uint32 uint32_t
#define DIO_HIGH 1
#define DIO_LOW 0
#define STD_HIGH 1
#define STD_LOW 0
#define STD_ACTIVE 0
#define STD_IDLE 1
#define STD_ON 1
#define STD_OFF 0
#define NULL_PTR NULL

#define E_OK 0
#define E_NOT_OK 1
#define E_SAFETY_INVALID_REP 2
#define E_SAFETY_INVALID_SEQ 3
#define E_SAFETY_INVALID_CRC 4
#define STD_MESSAGETYPE_REQUEST 0
#define STD_MESSAGETYPE_RESPONSE 1
#define STD_MESSAGERESULT_OK 0
#define STD_MESSAGERESULT_ERROR 1


#define GET_CHANNEL(ChannelID) \
    ((ChannelID) % 16)
#define GET_PORT(ChannelID) \
    ((ChannelID) < 16 ? GPIOA : \
    ((ChannelID) < 32 ? GPIOB : \
    ((ChannelID) < 48 ? GPIOC : \
    ((ChannelID) < 64 ? GPIOD : NULL))))
typedef uint8_t Std_TransformerClass;

typedef uint8_t Std_TransformerForwardCode;
typedef uint8_t Std_TransformerErrorCode;    




typedef uint8_t Std_ReturnType;




typedef struct{
    uint16_t vendorID;          // Vendor ID of the module
    uint16_t moduleID;          // Module ID of the module
    uint8_t   sw_major_version; // Major version of the software
    uint8_t   sw_minor_version; // Minor version of the software
    uint8_t   sw_patch_version; // Patch version of the software

} Std_VersionInfoType;


typedef struct {
    Std_TransformerErrorCode errorCode; // Error code indicating the type of error
    Std_TransformerClass transformerClass; // Class of the transformer
} Std_TransformerError;


typedef struct {

    Std_TransformerClass transformerClass;
} Std_TransformerForward;

typedef uint8_t Std_MessageTypeType;

typedef uint8_t Std_MessageResultType;



#endif // STD_TYPE_H