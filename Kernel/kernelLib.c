#include <stdarg.h>
#include <stdint.h>
#include <drivers/videoDriver.h>
#include <defs.h>
#include <kernelLib.h>

char snapShotFlag = 0;
static void decimalToHex(uint64_t value, char * buffer);

static char * strRegisters[] = {"RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "RBP", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15", "RIP", "RFLAGS", "RSP"};


void printRegisters(uint64_t * registers){
    if (snapShotFlag == 0){
        printf("Para ver los registros, presione ctrl + r\n", WHITE);
        return;
    }
    if(getCursorY() + 18 * getCharHeight() >= getScreenHeight()){
        clearScreen();
    }
    for (int i = 0; i < 18; i++){
        char buffer[20]; // Buffer to hold the hexadecimal representation
        decimalToHex(registers[i], buffer);
        printf(strRegisters[i], WHITE);
        printf(": ", WHITE);
        printf(buffer, WHITE);
        printf("\n", WHITE);
    }
    snapShotFlag = 0;
    
}

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