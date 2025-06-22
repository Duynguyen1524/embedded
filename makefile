# Makefile for STM32F103 Blink LED (no HAL, using SPL)

# Output file name
TARGET = ECU_HALAV2

# Compiler and flags
CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall -ffreestanding -nostdlib \
         -Icore \
         -ISPL/inc \
         -ISPL/src \
         -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER

LDFLAGS = -T stm32f103.ld -nostdlib -Wl,--gc-sections

# Source files
SRCS_C = main.c core/core_cm3.c $(wildcard SPL/src/*.c)
SRCS_S = startup_stm32f103.s
OBJS = $(SRCS_C:.c=.o) $(SRCS_S:.s=.o)

# Default target
all: $(TARGET).bin

# Compile .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile .s (assembly) files
%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files
$(TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Convert ELF to binary
%.bin: %.elf
	arm-none-eabi-objcopy -O binary $< $@

# Clean
clean:
	rm -f $(TARGET).elf $(TARGET).bin $(OBJS)
