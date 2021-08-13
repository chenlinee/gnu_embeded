AS_SRC:=$(wildcard *.s)
AS_OBJ:=$(addprefix $(OBJ_DIR)/, $(patsubst %.s, %.o, $(AS_SRC)))
C_SRC:=$(wildcard *.c)
C_OBJ:=$(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(C_SRC)))

COMPILE_DIR=

.PHONY: $(COMPILE_DIR)

ALL : $(AS_OBJ) $(C_OBJ) $(COMPILE_DIR)

$(addprefix $(OBJ_DIR)/, %.o) : %.s
	$(AS) $(ASFLAGS) -c $^ -o $@

$(addprefix $(OBJ_DIR)/, %.o) : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(COMPILE_DIR) :
	make -C $@
