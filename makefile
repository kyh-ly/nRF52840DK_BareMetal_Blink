.PHONY := all clean
.DEFAULT_GOAL := all

TARGET := firmware

ARCH := arm-none-eabi
MCU := cortex-m4

CC := $(ARCH)-gcc
AS := $(ARCH)-as
LD := $(ARCH)-ld
OBJDUMP := $(ARCH)-objdump
OBJCOPY := $(ARCH)-objcopy
OBJSIZE := $(ARCH)-size

SOURCE_DIR := source
BUILD_DIR := build
OBJECT_DIR := $(BUILD_DIR)/object
LINKER_SCRIPT_DIR := etc/linker
DIRS := $(BUILD_DIR) $(OBJECT_DIR)

LINKER_SCRIPT_FILE := $(LINKER_SCRIPT_DIR)/linkerScript.ld
CC_SRC_FILES := $(wildcard $(SOURCE_DIR)/*.c)
CC_OBJ_FILES := $(CC_SRC_FILES:$(SOURCE_DIR)/%.c=$(OBJECT_DIR)/%.o)

CC_FLAGS := -c -Wall -Werror -mcpu=$(MCU) -mthumb -O0 -std=c99
CC_FLAGS += -idirafter ./include -fdata-sections -ffunction-sections
CC_FLAGS += -ffreestanding
LD_FLAGS := -T $(LINKER_SCRIPT_FILE) -Map $(BUILD_DIR)/$(TARGET).map --gc-sections
LD_FLAGS += -nostartfiles -nolibc -nostdlib -nodefaultfiles
OBJDUMP_FLAGS := --disassemble-all $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).s
OBJCOPY_FLAGS := -O ihex $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex
OBJSIZE_FLAGS := $(BUILD_DIR)/$(TARGET).elf

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CC_FLAGS) $^ -o $@

$(BUILD_DIR)/$(TARGET).elf: $(AS_OBJ_FILES) $(CC_OBJ_FILES)
	$(LD) $(LD_FLAGS) $^ -o $@
	$(OBJDUMP) $(OBJDUMP_FLAGS)
	$(OBJCOPY) $(OBJCOPY_FLAGS)
	$(OBJSIZE) $(OBJSIZE_FLAGS) 

$(BUILD_DIR):
	mkdir --parents $(DIRS)

clean:
	rm -rf $(DIRS)

all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).elf

flash: all
	nrfjprog -f nrf52 --program build/firmware.hex --sectorerase
	nrfjprog -f nrf52 --pinreset
