# \
AS_SRC:=$(wildcard *.s) \
AS_OBJ:=$(addprefix $(OBJ_DIR)/, $(patsubst %.s, %.o, $(AS_SRC))) \
C_SRC:=$(wildcard *.c) \
C_OBJ:=$(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(C_SRC))) \

AS_SRC:=
AS_OBJ:=$(addprefix $(OBJ_DIR)/, $(patsubst %.s, %.o, $(AS_SRC)))
C_SRC:=heap.c
C_OBJ:=$(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(C_SRC)))

SUB_DIR=

.PHONY: $(SUB_DIR)

ALL : $(AS_OBJ) $(C_OBJ) $(SUB_DIR)

$(addprefix $(OBJ_DIR)/, %.o) : %.s
	$(AS) $(ASFLAGS) -c $^ -o $@

$(addprefix $(OBJ_DIR)/, %.o) : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(SUB_DIR) :
	make -C $@
