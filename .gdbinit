# choose target arch
set architecture armv7

# load elf file(include debug information)
file build/ciios.elf

# link to gdb server
target remote 127.0.0.1:12345