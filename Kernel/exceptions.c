#include "exceptions.h"
#include <drivers/videoDriver.h>
#include <defs.h>

#define ZERO_EXCEPTION 0

static void divisionByZero();
static void invalidOpcode();
static void decimalToHex(uint64_t value, char * buffer);

static char * strRegisters[18] = {"RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "RBP", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15", "RIP", "RFLAGS", "RSP"};

static void decimalToHex(uint64_t value, char * buffer){
    char hexDigits[] = "0123456789ABCDEF";
    char temp[17]; // 16 digits + null terminator 
    int i = 0;

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = 'x';
        buffer[2] = '0';
        buffer[3] = '\0';
        return;
    }

    while (value > 0) {
        temp[i++] = hexDigits[value % 16];
        value /= 16;
    }

    // Prefix "0x"
    buffer[0] = '0';
    buffer[1] = 'x';

    // Reverse the string
    int j = 2;
    while (i > 0) {
        buffer[j++] = temp[--i];
    }
    buffer[j] = '\0';
}

void exceptionDispatcher(int exception){
    if (exception == ZERO_EXCEPTION) {
        divisionByZero();
    } else {
        invalidOpcode();
    }
}

static void divisionByZero() {
    print("Division by zero exeption\n", RED);
   // printAllRegisters();
    puts("\n");
}

static void invalidOpcode() {
    print("Invalid opcode exception\n", RED);
    // printAllRegisters();
    puts("\n");
}