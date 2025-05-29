include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin

#C_SOURCES := $(filter-out _loader.c, $(wildcard *.c))
C_SOURCES=$(wildcard [^_]*.c)

#ASM_SOURCES := asm/syscalls.asm
ASM_SOURCES=$(wildcard asm/*.asm)

#OBJ := $(C_SOURCES:.c=.o) _loader.o asm/syscalls.o
OBJ=$(ASM_SOURCES:asm/%.asm=obj/%.asm.o)


all: $(MODULE)
	
	
#### Compilar cada archivo C a .o
####%.o: %.c
####	$(GCC) $(GCCFLAGS) -c $< -o $@

# Binario final con linker script
####$(MODULE): $(OBJ)
$(MODULE): $(ASM_SOURCES) $(OBJ)
	######$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld $(OBJ)  $(C_SOURCES) -o ../$(MODULE)
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld _loader.c $(OBJ)  $(C_SOURCES) -o ../$(MODULE)
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld _loader.c $(OBJ) $(C_SOURCES) -Wl,--oformat=elf64-x86-64 -o ../0000-sampleCodeModule.elf


#### Compilar ASM con nasm
####asm/syscalls.o: asm/syscalls.asm
####	$(ASM) $(ASMFLAGS) -felf64 $< -o $@
obj/%.asm.o : asm/%.asm
	mkdir -p obj
	$(ASM) $(ASMFLAGS) $< -o $@


clean:
	rm -rf *.o asm/*.o

.PHONY: all clean
