#include <stdarg.h>
#include <stdint.h>
#include "include/syscalls.h"
#include "include/libC.h"

#define STDIN 0
#define STDOUT 1
#define USER_LENGTH 31

void print(const char * string, va_list list);
char* numToString(int num);

// Lectura

char readChar(){
    char buffer[1] = {0};
    syscall_read(STDIN, buffer, 1);
    return buffer[0];
}

int scanf(char * buffer){
    int i = 0;
    while(1){
        printCursor();
        
        char c = readChar();
        if(c == '\b' && i== 0){
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
}

int atoi(char * string){
    int ans = 0;
    for(int i = 0 ; string[i] != 0 ; i++){
        ans = ans * 10 + string[i] - '0';
    }
    return ans;
}

// Escritura

void putChar(char c, int fd){
    syscall_write(fd, &c, 1);
}

void putColorChar(char c, int fd, int color){
    syscall_colorWrite(&c, color);
}

void printCursor(){
    syscall_drawCursor();
}

void puts(char * string){
    syscall_write(STDOUT, string, strlen(string));
    putChar('\n', STDOUT);
}

void print(const char * string, va_list list){
    for(int i = 0; string[i] != 0 ; i++){
        if(string[i] == '%' && string[i + 1] != 0){
            switch (string[i+1]){
                case 'd':
                    i++;
                    char *numStr = numToString(va_arg(list, int));
                    for (int j = 0; numStr[j] != '\0'; j++) {
                        putChar(numStr[j], STDOUT);
                    }
                break;
                case 's':
                    i++;
                    char *str = va_arg(list, char *);
                    for (int j = 0; str[j] != '\0'; j++) {
                        putChar(str[j], STDOUT);
                    }
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

void printColor(char * string, int color){
    int i = 0;
    while(string[i] != '\0'){
        putColorChar(string[i], 1, color);
        i++;
    }
}


// Utilidad

int getSecondsUser(){
    uint64_t seconds;
    syscall_seconds(&seconds);
    return seconds;
}

int getMinutesUser(){
    uint64_t minutes;
    syscall_minutes(&minutes);
    return minutes;
}

int getHoursUser(){
    uint64_t hours;
    syscall_hours(&hours);
    return hours;
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