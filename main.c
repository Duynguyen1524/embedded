#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "Dio.h"
#include "Std_Types.h"

// Delay using TIM2
void delay_ms(uint16_t ms)
{
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < ms);
}

void init_gpio()
{
    // Enable clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // PC13 and PA0 as output (LEDs)
    GPIO_InitTypeDef gpio_out;
    gpio_out.GPIO_Pin = GPIO_Pin_13;
    gpio_out.GPIO_Speed = GPIO_Speed_2MHz;
    gpio_out.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &gpio_out);

    gpio_out.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &gpio_out);

    // PB1 as input (e.g., button)
    GPIO_InitTypeDef gpio_in;
    gpio_in.GPIO_Pin = GPIO_Pin_1;
    gpio_in.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &gpio_in);

    // TIM2: 1ms per tick
    TIM_TimeBaseInitTypeDef tim;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_Period = 0xFFFF;
    tim.TIM_Prescaler = 8000 - 1;
    TIM_TimeBaseInit(TIM2, &tim);
    TIM_Cmd(TIM2, ENABLE);
}

int main(void)
{
    init_gpio();

    // Channel IDs:
    uint8_t CH_PC13 = 45;  // PC13
    uint8_t CH_PA0 = 0;    // PA0
    uint8_t CH_PB1 = 17;   // PB1 (input)

    // Port IDs
    uint8_t PORT_A = 0;
    uint8_t PORT_C = 2;

    // Test WriteChannel
    Dio_WriteChannel(CH_PA0, DIO_HIGH);  // PA0 = HIGH
    delay_ms(500);
    Dio_WriteChannel(CH_PA0, DIO_LOW);   // PA0 = LOW
    delay_ms(500);

    // Test ReadChannel (PB1)
    Dio_LevelType button = Dio_ReadChannel(CH_PB1);
    if (button == DIO_HIGH)
        Dio_WriteChannel(CH_PA0, DIO_HIGH);  // If button pressed, turn PA0 on

    // Test FlipChannel (PC13)
    for (int i = 0; i < 5; i++)
    {
        Dio_FlipChannel(CH_PC13);
        delay_ms(200);
    }

    // Test WritePort (PORT C)
    Dio_WritePort(PORT_C, 0x2000);  // Write PC13 HIGH only
    delay_ms(200);
    Dio_WritePort(PORT_C, 0x0000);  // All LOW
    delay_ms(200);

    // Test ReadPort (PORT A)
    Dio_PortLevelType porta_state = Dio_ReadPort(PORT_A);
    if (porta_state & (1 << 0))
        Dio_WriteChannel(CH_PC13, DIO_HIGH);  // If PA0 is HIGH, light PC13

    // Test WriteChannelGroup
    Dio_ChannelGroupType ledGroup = {
        .port = PORT_A,     // GPIOA
        .mask = 0x01,       // Only bit 0
        .offset = 0
    };
    Dio_WriteChannelGroup(&ledGroup, 0x01);  // Set PA0 HIGH
    delay_ms(200);
    Dio_WriteChannelGroup(&ledGroup, 0x00);  // Set PA0 LOW

    while (1)
    {
        // Blink PC13 forever
        Dio_FlipChannel(CH_PC13);
        delay_ms(500);
    }
}
