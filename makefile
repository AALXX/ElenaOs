ASM=nasm
CC=x86_64-elf-gcc 
CC_LINKER= x86_64-elf-ld

BUILD_DIR=build
BOOTLOADER_DIR=src/bootloader
KERNEL_DIR=src/kernel

HEADERS_C = $(wildcard $(KERNEL_DIR)/*.h) \
										$(wildcard $(KERNEL_DIR)/*/*.h) \
										$(wildcard $(KERNEL_DIR)/*/*/*.h) \
										$(wildcard $(KERNEL_DIR)/*/*/*/*.h)

SOURCES_C = $(wildcard $(KERNEL_DIR)/*.c) \
										$(wildcard $(KERNEL_DIR)/*/*.c) \
										$(wildcard $(KERNEL_DIR)/*/*/*.c) \
										$(wildcard $(KERNEL_DIR)/*/*/*/*.c) \

OBJECTS_C = $(patsubst $(KERNEL_DIR)/%.c, $(BUILD_DIR)/kernel/c/%.obj, $(SOURCES_C))


.PHONY: all image kernel bootloader clean always

all: image 

#
# Floppy image
#
image: $(BUILD_DIR)/BootLoader.bin

$(BUILD_DIR)/BootLoader.bin: bootloader kernel
	cat $(BUILD_DIR)/stage1.bin $(BUILD_DIR)/Kernel.bin > $(BUILD_DIR)/BootLoader.bin

#
# Bootloader
#
bootloader: stage1 stage2

stage1: $(BUILD_DIR)/stage1.bin

$(BUILD_DIR)/stage1.bin: always
	$(ASM) $(BOOTLOADER_DIR)/stage1/boot.asm -f bin -o $(BUILD_DIR)/stage1.bin

stage2: $(BUILD_DIR)/stage2.o

$(BUILD_DIR)/stage2.o: always
	$(ASM) $(BOOTLOADER_DIR)/stage2/stage2.asm -f elf64 -o $(BUILD_DIR)/stage2.o


kernel: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: $(OBJECTS_C)
	@$(CC_LINKER) -T"linker.ld" -o $@ $^
	@echo "--> Created:  kernel.bin"

$(BUILD_DIR)/kernel/c/%.obj: $(KERNEL_DIR)/%.c $(HEADERS_C)
	@mkdir -p $(@D)
	@$(CC) -Ttext 0x8000  -ffreestanding -mno-red-zone -m64 -c -o $@ $<
	@echo "--> Compiled: " $<

$(BUILD_DIR)/kernel.o: always
	$(CC_LINKER) -T"linker.ld"

#
# Always
#
always:
	mkdir -p $(BUILD_DIR)
	rm -rf $(BUILD_DIR)/*

#
# Clean
#
clean:
	rm -rf $(BUILD_DIR)/*


build-run:
	make
	qemu-system-x86_64.exe build/BootLoader.bin