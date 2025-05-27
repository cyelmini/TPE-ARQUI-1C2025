#include <stdarg.h>
#include "include/syscalls.h"
#include "include/libC.h"

#define STDIN 0
#define STDOUT 1

#define USER_LENGTH 10

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
    int ini_cursor_y = syscall_cursorY();
    while(1){
        char c = readChar();
        if(c == '\b' && ini_cursor_y == syscall_cursorY() && syscall_cursorY() <= USER_LENGTH){
            // if user is not trying to erase the set text in the command line, continue
            continue;
        }
        putChar(c, 1);

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
    syscall_write(STDOUT, &c, strlen(&c));
}

void puts(char * string){
    for(int i = 0 ; string[i] != 0 ; i++){
        putChar(string[i], STDOUT);
    }
    putChar('\n', STDOUT);
}

void print(const char * string, va_list list){
    int i = 0;
    while(string[i] != 0){
        if(string[i] == '%' && string[i + 1] != 0){
            switch (string[i]){
                case 'd':
                    putChar(*numToString(va_arg(list, int)), STDOUT);
                break;
                case 's':
                    puts(va_arg(list, char*));
                break;
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

// Utilidad

int strlen(char * s){
    int i = 0;
    while(*s){
        i++;
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

