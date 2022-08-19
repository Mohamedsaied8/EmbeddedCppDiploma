# Name of the binaries.
PROJ_NAME=stm32f1-template
MKDIR = "C:\Program Files (x86)\Git\bin\mkdir.exe" -p

######################################################################
#                         SETUP TOOLS                                #
######################################################################

# This is the path to the toolchain
# (we don't put our toolchain on $PATH to keep the system clean)
TOOLS_DIR = 'C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/11.2 2022.02\bin'
#/opt/gcc-arm-embedded/gcc-arm-none-eabi-5_2-2015q4/bin

# The tools we use
CC      = $(TOOLS_DIR)/arm-none-eabi-gcc
CXX      = $(TOOLS_DIR)/arm-none-eabi-g++
OBJCOPY = $(TOOLS_DIR)/arm-none-eabi-objcopy
GDB     = $(TOOLS_DIR)/arm-none-eabi-gdb
AS      = $(TOOLS_DIR)/arm-none-eabi-as

## Preprocessor options

# directories to be searched for header files
INCLUDE = $(addprefix -I,$(INC_DIRS))

# #defines needed when working with the STM library
DEFS    = -DUSE_STDPERIPH_DRIVER
# if you use the following option, you must implement the function
#    assert_failed(uint8_t* file, uint32_t line)
# because it is conditionally used in the library
# DEFS   += -DUSE_FULL_ASSERT

##### Assembler options

AFLAGS  = -mcpu=cortex-m4
AFLAGS += -mthumb
AFLAGS += -mthumb-interwork
AFLAGS += -mlittle-endian
AFLAGS += -mfloat-abi=soft
AFLAGS += -mfpu=fpv4-sp-d16

## Compiler options

CFLAGS  = -ggdb
# please do not optimize anything because we are debugging
CFLAGS += -O0
CFLAGS += -Wall -Wextra -Warray-bounds
CFLAGS += -specs=nosys.specs #in order to get rid of _sbrk linker error
CFLAGS += $(AFLAGS)

## Linker options

# tell ld which linker file to use
# (this file is in the current directory)
LFLAGS  = -Tstm32_flash.ld


######################################################################
#                         SETUP SOURCES                              #
######################################################################

# This is the directory containing the firmware package,
# the unzipped folder downloaded from here:
# http://www.st.com/web/en/catalog/tools/PF257904
STM_ROOT         =../STM32F10x_StdPeriph_Lib_V3.5.0

# This is where the source files are located,
# which are not in the current directory
# (the sources of the standard peripheral library, which we use)
# see also "info:/make/Selective Search" in Konqueror
MY_SRC_DIR       = ./src
STM_SRC_DIR      = $(STM_ROOT)/Libraries/STM32F10x_StdPeriph_Driver/src
STM_SRC_DIR     += $(STM_ROOT)/Utilities/Third_Party
STM_STARTUP_DIR += ./startup
#/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TrueSTUDIO

# Tell make to look in that folder if it cannot find a source
# in the current directory
vpath %.c $(MY_SRC_DIR)
vpath %.cpp $(MY_SRC_DIR)
vpath %.c $(STM_SRC_DIR)
vpath %.cpp $(STM_STARTUP_DIR)


################################################################################
#                         SETUP HEADER FILES                                   #
################################################################################

# The header files we use are located here
INC_DIRS  = ./headers
INC_DIRS += $(STM_ROOT)/Utilities/Third_Party
INC_DIRS += $(STM_ROOT)/Libraries/CMSIS/Include
#INC_DIRS += $(STM_ROOT)/Libraries/CMSIS/ST/STM32F10xx/Include
INC_DIRS += $(STM_ROOT)/Libraries/CMSIS/CM3/CoreSupport
INC_DIRS += $(STM_ROOT)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
INC_DIRS += $(STM_ROOT)/Libraries/STM32F10x_StdPeriph_Driver/inc
INC_DIRS += $(STM_ROOT)/Project/STM32F10x_StdPeriph_Template


################################################################################
#                   SOURCE FILES TO COMPILE                                    #
################################################################################

# My source files
#SRCS   = main.c

# Contains initialisation code and must be compiled into
# our project. This file is in the current directory and
# was writen by ST.
SRCS  += system_stm32f10x.c

# Startup file written by ST
# The assembly code in this file is the first one to be
# executed. Normally you do not change this file.
ASRC = startup_stm32f10x.s
CPP_SRCS = crt0.cpp crt0_init_ram.cpp crt1.cpp int_vect.cpp led.cpp main.cpp
# in case we have to many sources and don't want
# to compile all sources every time
OBJS = $(SRCS:.c=.o)
#OBJS += $(ASRC:.s=.o)
OBJS +=$(CPP_SRCS:.cpp=.o)
STM_SRC_DIR_C = stm32f10x_gpio.c stm32f10x_rcc.c
OBJS += $(STM_SRC_DIR_C:.c=.o)


######################################################################
#                         SETUP TARGETS                              #
######################################################################

TEMP_DIR = ./temp
OUT_DIR = ./out

.PHONY: all

all: $(PROJ_NAME).elf

%.o : %.c
	@echo "[Compiling  ]  $^"
#	@mkdir ${TEMP_DIR}
	@$(CC) -c -o $(TEMP_DIR)/$@ $(INCLUDE) $(DEFS) $(CFLAGS) $^

%.o : %.cpp
	@echo "[Compiling  ]  $^"
#	@mkdir -p ${TEMP_DIR}
	@$(CXX) -c -o $(TEMP_DIR)/$@ $(INCLUDE) $(DEFS) $(CFLAGS) $^

%.o : %.s
	@echo "[Assembling ] $^"
#	@mkdir -p ${TEMP_DIR}
	@$(AS) $(AFLAGS) $< -o $(TEMP_DIR)/$@

$(PROJ_NAME).elf: $(OBJS)
	@echo "[Linking    ]  $@"
#	@mkdir -p ${OUT_DIR}
	@$(CXX) $(CFLAGS) $(LFLAGS) $(foreach file, $^, $(TEMP_DIR)/$(file)) -o $(OUT_DIR)/$@
	@$(OBJCOPY) -O ihex $(OUT_DIR)/$(PROJ_NAME).elf   $(OUT_DIR)/$(PROJ_NAME).hex
	@$(OBJCOPY) -O binary $(OUT_DIR)/$(PROJ_NAME).elf $(OUT_DIR)/$(PROJ_NAME).bin

clean:
	@rm -f *.o $(OUT_DIR)/* $(TEMP_DIR)/*

flash: all
	st-flash --flash=64k write $(OUT_DIR)/$(PROJ_NAME).bin 0x8000000

debug:
# before you start gdb, you must start st-util
	$(GDB) -tui $(OUT_DIR)/$(PROJ_NAME).hex
