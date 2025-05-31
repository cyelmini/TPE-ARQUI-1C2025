#include <stdarg.h>
#include <stdint.h>
#include "include/syscalls.h"
#include "include/libC.h"

#define STDIN 0
#define STDOUT 1

#define USER_LENGTH 6

void print(const char * string, va_list list);
char* numToString(int num);
static void decimalToHex(uint64_t value, char * buffer);

static char * strRegisters[19] = {"RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "RBP", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15", "RIP", "RFLAGS", "RSP"};

// Lectura

char readChar(){
    char buffer[1] = {0};
    syscall_read(STDIN, buffer, 1);
    return buffer[0];
}


int scanf(char * buffer) {
    int idx = 0;
    int yUserPos = syscall_getCursorY(); // We save the Y position of the user, so we can check if the user tries to eliminate "$User: " from the command line
    while (1) {
        printCursor();
        char c = readChar();
        if(c == '\b' && syscall_getCursorX() <= USER_LENGTH && syscall_getCursorY() == yUserPos){
            continue;
        }   
        putChar(c, 1); // We print the character

        //We handle the different cases of the special characters
        if (c != -1 && c != 0) {
            if (c == '\b' && idx > 0) {
                idx--;
            } else if (c == '\n') {
                buffer[idx] = '\0';
                return idx;
            } else if (c != '\t') {
                buffer[idx] = c;
                idx++;
            }
        }
    }
    return -1;
}


/*
int scanf(char * buffer){
    int i = 0;
    int ini_cursor_y = syscall_getCursorY();
    int ini_cursor_x = syscall_getCursorX();
    while(1){
        printCursor();
        
        char c = readChar();
        if(c == '\b' && ini_cursor_y == syscall_getCursorY() && syscall_getCursorX() <= USER_LENGTH){
            // if user is trying to erase the set text in the command line, continue
            continue;
        }
        putChar(c, STDOUT);

        // special characters
        if(c != -1 && c != 0){
            if(c == '\b' && i > 0){
                i--;
            } else if (c == '\n'){
                buffer[i] = 0;
                return i;
            } else if (c != '\t'){
                buffer[i] = c;
                i++;
            }
        }
    }
    return -1;
} */

int atoi(char * string){
    int ans = 0;
    for(int i = 0 ; string[i] != 0 ; i++){
        ans = ans * 10 + string[i] - '0';
    }
    return ans;
}

// Escritura

void printAllRegisters(){
    puts("\n");
    char hexNumber[19];
    uint64_t registers[18];
    syscall_getRegisters(registers);
        for (int i = 0; i < 19; i++)
        {
           printf("%s: ", strRegisters[i]);
           decimalToHex(registers[i], hexNumber);
           printf("%s   ", hexNumber);
        }
}

void putChar(char c, int fd){
    syscall_write(fd, &c, 1);
}

void printCursor(){
    syscall_cursor();
}

void puts(char * string){
    syscall_write(STDOUT, string, strlen(string));
}

void print(const char * string, va_list list){
    for(int i = 0; string[i] != 0 ; i++){
        if(string[i] == '%' && string[i + 1] != 0){
            switch (string[i+1]){
                case 'd':
                    i++;
                    putChar(*numToString(va_arg(list, int)), STDOUT);
                break;
                case 's':
                    i++;
                    puts(va_arg(list, char *));
                break;
                case 'c':
                    i++;
                    putChar(va_arg(list, int), STDOUT);
                break;
                default:
                    putChar('%', STDOUT);
                break;
            }
        } else {
            putChar(string[i], STDOUT);
        }
    }
}

void printf(const char * string, ...){
    va_list list;
    va_start(list, string);
    print(string, list);
    va_end(list);
}

// Utilidad

int getSeconds(){
    uint64_t seconds;
    syscall_seconds(&seconds);
    return seconds;
}

int getMinutes(){
    uint64_t minutes;
    syscall_minutes(&minutes);
    return minutes;
}

int getHours(){
    uint64_t hours;
    syscall_hours(&hours);
    return hours - 3;
}

int strlen(char * s){
    int i = 0;
    while(*s){
        i++;
        s++;
    }
    return i;
}

char * numToString(int num) {
    static char buffer[21]; 
    char *ptr = buffer + sizeof(buffer) - 1;
    unsigned long long n;
    int isNegative = 0;

    *ptr = '\0';

    if (num == 0) {
        *(--ptr) = '0';
        return ptr;
    }

    if (num < 0) {
        isNegative = 1;
        n = (unsigned long long)(-(long long)num);
    } else {
        n = (unsigned long long)num;
    }

    while (n != 0) {
        *(--ptr) = (n % 10) + '0';
        n /= 10;
    }

    if (isNegative)
        *(--ptr) = '-';

    return ptr;
}

int strcmp(const char * s1, const char * s2){
    while(*s1 && (*s1 == *s2)){
        s1++;
        s2++;
    }
    return *s1 - *s2;
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