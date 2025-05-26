#include "include/libC.h"

#define STDOUT 1

void print(const char * string, va_list list);
char* numToString(int num);

int strlen(char * s){
    int i = 0;
    while(*s){
        i++;
    }
    return i;
}

void putChar(char c, int fd){
    sys_call_write(STDOUT, &c, strlen(&c));
}

void puts(char * string){
    for(int i = 0 ; string[i] != 0 ; i++){
        putChar(string[i], STDOUT);
    }
    putChar('\n', STDOUT);
}
/*
int scanf(char * buffer){
    int i = 0;

    while(1){
        char c = readChar();
        if(c == '\b'){

        }
    }
} */

char * numToString(int num) {
    static char buffer[21]; // Enough for 64-bit int
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

void print(const char * string, va_list list){
    int i = 0;
    while(string[i] != 0){
        if(string[i] == '%' && string[i+1] != 0){
            switch (string[i]){
                case 'd':
                    putChar(*numToString(va_arg(list, int)), STDOUT);
                break;;
                case 's':
                    puts(va_arg(list, char*));
                break;;
                case 'c':
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