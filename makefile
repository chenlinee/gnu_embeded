COMPILE_DIR=bsp src drivers freertos
ROOT=$(shell pwd)
export OBJ_DIR=$(ROOT)/build/objs

ARM_PATH=/home/ciichen/lib/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-
export CC=$(ARM_PATH)gcc
export AS=$(ARM_PATH)as
LD=$(ARM_PATH)ld
OBJCOPY=$(ARM_PATH)objcopy
export CFLAGS=-Wall -O0 -std=c99 -nodefaultlibs -nostdlib -nostartfiles -march=armv7-m -mtune=cortex-m3 -mthumb -g -funsigned-char -I $(ROOT)/drivers/inc -I $(ROOT)/inc -I $(ROOT)/freertos/include -I $(ROOT)/freertos/portable
export ASFLAGS=--warn -march=armv7-m -mcpu=cortex-m3 -mthumb -g
OBJFLAGS=-j .isr_vector -j .text -j .data --set-section-flags .isr_vector=alloc,load,contents --set-section-flags .bss=alloc,load,contents

# export C_INC=-I $(ROOT)/drivers/inc -I $(ROOT)/inc -I $(ROOT)/freertos/include -I $(ROOT)/freertos/portable
LIBGCC=${shell ${CC} -mthumb -march=armv7-m -print-libgcc-file-name}
LIBC=${shell ${CC} -mthumb -march=armv7-m -print-file-name=libc.a}
LIBS=$(ROOT)/drivers/lib/libdriver.a

.PHONY: build link $(COMPILE_DIR) mk_build_dir rebuild clean qemu

build : link
link : $(COMPILE_DIR)
	$(LD) -T standalone.ld $(OBJ_DIR)/* -static -o build/ciios.elf $(LIBGCC) $(LIBC) $(LIBS)
	$(OBJCOPY) -O binary $(OBJFLAGS) build/ciios.elf build/ciios.bin

$(COMPILE_DIR) : mk_build_dir
	make -C $@

mk_build_dir : 
	@if [ ! -d "build" ]; then \
		mkdir -p build/objs; \
	elif [ ! -d "build/objs" ]; then\
		mkdir build/objs; \
	fi

rebuild : clean build
clean : 
	-rm -r build/*

qemu-debug :
	@qemu-system-arm -machine lm3s6965evb \
			-cpu cortex-m3 -nographic \
			-gdb tcp::12345 \
			-S -kernel build/ciios.bin

# uart0, uart1
# -serial /dev/pts/5 -serial /dev/pts/6
qemu :
	@qemu-system-arm -machine lm3s6965evb \
			-cpu cortex-m3 -nographic \
			-kernel build/ciios.bin
