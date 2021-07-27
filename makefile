ARM_PATH=/usr/local/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-
export CC=$(ARM_PATH)gcc
export AS=$(ARM_PATH)as
export LD=$(ARM_PATH)ld
OBJCOPY=$(ARM_PATH)objcopy
export C_FLAGS=-Wall -O0 -std=c99 -nodefaultlibs -nostdlib -nostartfiles -march=armv7-m -mtune=cortex-m3 -mthumb -g
export C_FLAGS+=-I drivers
export AS_FLAGS=--warn -march=armv7-m -mcpu=cortex-m3 -mthumb -g
OBJFLAGS=-j .isr_vector -j .text -j .data --set-section-flags .isr_vector=alloc,load,contents --set-section-flags .bss=alloc,load,contents

COMPILE_DIR=bsp src drivers
ROOT=$(shell pwd)
export OBJ_DIR=$(ROOT)/build/objs

LIBGCC=${shell ${CC} -mthumb -march=armv7-m -print-libgcc-file-name}
LIBC=${shell ${CC} -mthumb -march=armv7-m -print-file-name=libc.a}
LIBS=$(ROOT)/drivers/libdriver.a

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

qemu :
	qemu-system-arm -machine lm3s6965evb \
			-cpu cortex-m3 -nographic \
			-gdb tcp::12345 \
			-S -kernel build/ciios.bin
