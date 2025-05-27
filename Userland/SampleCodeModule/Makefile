include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin

C_SOURCES := $(filter-out _loader.c, $(wildcard *.c))
ASM_SOURCES := asm/syscalls.asm

OBJ := $(C_SOURCES:.c=.o) _loader.o asm/syscalls.o

all: $(MODULE)

# Compilar ASM con nasm
asm/syscalls.o: asm/syscalls.asm
	$(ASM) $(ASMFLAGS) -felf64 $< -o $@

# Compilar cada archivo C a .o
%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

# Binario final con linker script
$(MODULE): $(OBJ)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld $(OBJ) -o ../$(MODULE)

clean:
	rm -rf *.o asm/*.o

.PHONY: all clean
