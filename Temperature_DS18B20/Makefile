PROJECT_NAME = test

BUILDDIR = build

EVAL = inc/STM324x7I_EVAL
CMSIS = inc/CMSIS/Include
PERIPH = inc/STM32F4xx_StdPeriph_Driver
DEVICE = inc/STM32F4xx/Include
DISCOVERY = inc

SOURCES += $(PERIPH)/src/stm32f4xx_gpio.c \
		   $(PERIPH)/src/stm32f4xx_rcc.c \
		   $(PERIPH)/src/stm32f4xx_usart.c \
		   $(PERIPH)/src/misc.c				

SOURCES += startup_stm32f40_41xxx.s
SOURCES += system_stm32f4xx.c
SOURCES += src/main.c \
		   src/usart.c \
		   src/DS18B20.c \
		   src/delay.c

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

INCLUDES += -I$(EVAL) \
	    -I$(CMSIS) \
	    -I$(PERIPH)/inc \
		-I$(DISCOVERY) \
	    -I$(DEVICE) \
	    -I.

ELF = $(BUILDDIR)/$(PROJECT_NAME).elf
HEX = $(BUILDDIR)/$(PROJECT_NAME).hex
BIN = $(BUILDDIR)/$(PROJECT_NAME).bin

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
GDB = arm-none-eabi-gdb

CFLAGS  = -O0 -g -Wall -I.\
   	  -mcpu=cortex-m4 -mthumb \
   	  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp \
   	  $(INCLUDES) -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx

LDSCRIPT = STM32F417IGHx_FLASH.ld
LDFLAGS += -T$(LDSCRIPT) -mthumb -mcpu=cortex-m4 -nostdlib

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.S
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

flash: $(BIN)
	st-flash write $(BIN) 0x8000000

debug: $(ELF)
	$(GDB) -tui $(ELF)

all: $(HEX) $(BIN)

.PHONY: clean
clean:
	rm -rf build
