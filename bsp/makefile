AS_SRC:=$(wildcard *.s)
AS_OBJ:=$(addprefix $(OBJ_DIR)/, $(patsubst %.s, %.o, $(AS_SRC)))
C_SRC:=$(wildcard *.c)
C_OBJ:=$(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(C_SRC)))

ALL : $(AS_OBJ) $(C_OBJ)

$(AS_OBJ) : $(AS_SRC)
	$(AS) $(AS_FLAGS) -c $^ -o $@

$(C_OBJ) : $(C_SRC)
	$(CC) $(C_FLAGS) -c $^ -o $@
