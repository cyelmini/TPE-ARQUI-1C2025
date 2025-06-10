#include <stdarg.h>
#include <stdint.h>
#include "include/syscalls.h"
#include "include/libC.h"

#define STDIN 0
#define STDOUT 1
#define USER_LENGTH 31

// ---- Lectura de entrada ----

// Lee un carácter desde la entrada estándar
char readChar(){
    char buffer[1] = {0};
    syscall_read(STDIN, buffer, 1);
    return buffer[0];
}

// Escanea una línea desde stdin con eco y control de caracteres especiales
int scanf(char * buffer){
    int i = 0;
    while(1){
        printCursor();

        char c = readChar();
        if(c == '\b' && i == 0){
            continue; // Ignora retroceso si no hay caracteres escritos
        }

        putChar(c, STDOUT); // Muestra el carácter en pantalla

        // Procesamiento de caracteres especiales
        if(c != -1 && c != 0){
            if(c == '\b' && i > 0){
                i--;
            } else if (c == '\n'){
                buffer[i] = 0; // Fin de cadena
                return i;
            } else if (c != '\t'){ // Ignora tabulaciones
                buffer[i] = c;
                i++;
            }
        }
    }
    return -1;
}

// ---- Escritura de salida ----

// Imprime un carácter en pantalla (o en archivo)
void putChar(char c, int fd){
    syscall_write(fd, &c, 1);
}

// Imprime un carácter con color
void putColorChar(char c, int fd, int color){
    syscall_colorWrite(&c, color);
}

// Imprime el cursor visual en pantalla
void printCursor(){
    syscall_drawCursor();
}

// Imprime un string con salto de línea al final
void puts(char * string){
    syscall_write(STDOUT, string, strlen(string));
    putChar('\n', STDOUT);
}

// Imprime un string con color
void printColor(char * string, int color){
    int i = 0;
    while(string[i] != '\0'){
        putColorChar(string[i], STDOUT, color);
        i++;
    }
}

static void print(const char * string, va_list list){
    for(int i = 0; string[i] != 0 ; i++){
        if(string[i] == '%' && string[i + 1] != 0){
            switch (string[i + 1]){
                case 'd': {
                    i++;
                    char *numStr = numToString(va_arg(list, int));
                    for (int j = 0; numStr[j] != '\0'; j++) {
                        putChar(numStr[j], STDOUT);
                    }
                    break;
                }
                case 's': {
                    i++;
                    char *str = va_arg(list, char *);
                    for (int j = 0; str[j] != '\0'; j++) {
                        putChar(str[j], STDOUT);
                    }
                    break;
                }
                case 'c': {
                    i++;
                    putChar(va_arg(list, int), STDOUT);
                    break;
                }
                default:
                    putChar('%', STDOUT); // Si no reconoce formato, imprime %
                    break;
            }
        } else {
            putChar(string[i], STDOUT);
        }
    }
}

// Imprime un string formateado con soporte para %d, %s y %c
void printf(const char * string, ...){
    va_list list;
    va_start(list, string);
    print(string, list);
    va_end(list);
}

// ---- Funciones de tiempo del sistema ----

// Devuelve los segundos actuales desde el sistema
int getSecondsUser(){
    uint64_t seconds;
    syscall_seconds(&seconds);
    return seconds;
}

// Devuelve los minutos actuales desde el sistema
int getMinutesUser(){
    uint64_t minutes;
    syscall_minutes(&minutes);
    return minutes;
}

// Devuelve las horas actuales desde el sistema
int getHoursUser(){
    uint64_t hours;
    syscall_hours(&hours);
    return hours;
}

// ---- Funciones auxiliares de strings y números ----

// Devuelve la longitud de una cadena
int strlen(char * s){
    int i = 0;
    while(*s){
        i++;
        s++;
    }
    return i;
}

// Convierte una cadena numérica en un entero
int atoi(char * string){
    int ans = 0;
    for(int i = 0 ; string[i] != 0 ; i++){
        ans = ans * 10 + string[i] - '0';
    }
    return ans;
}

// Convierte un entero en string (hasta 20 cifras)
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

// Compara dos strings (retorna 0 si son iguales)
int strcmp(const char * s1, const char * s2){
    while(*s1 && (*s1 == *s2)){
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
