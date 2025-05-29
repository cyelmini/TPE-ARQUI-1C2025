#include "include/libC.h"
#include "include/shell.h"
#include "include/syscalls.h"

#define BUFFER_SIZE 2048
#define MAX_ARGS 10
#define MAX_ARG_LEN 50

static char * commands[] = {"help", "playGolf", "time", "printRegisters"};
static int commands_size = 4; 

static void clearBuffer(char * buffer);
static char * filletEntry(char * str);
char ** filletArguments(char * arguments);


void initializeShell(){
    printf("Bienvenido al mejor sistema operativo en el universo.\nIngrese 'help' para conocer los comandos disponibles, o 'help $COMMAND' para saber mas sobre un comando.\n\n");
    scanEntry();
}

void scanEntry() {
    while(1){
        printf("$USER@$DEVICE_NAME:/path/path$ ");

        char buffer[BUFFER_SIZE] = {0};

        if (syscall_getCursorY() > syscall_getScreenHeight() - 1) {
            clearScreen();
        }

        int len = scanf(buffer);

        if (len > 0 && buffer[0] != '\n') {
            entryHandler(buffer);
        }

        clearBuffer(buffer);
    }
    
}


void clearBuffer(char * buffer){
    for(int i = 0; i < BUFFER_SIZE; i++){
        buffer[i] = 0;
    }
}

// separa un string cuando encuentra el primer espacio devolviendo un puntero a la segunda mitad del string
char * filletEntry(char * str){
    char * fillet;
    while(*str != ' '){
        str++;
    }
    fillet = str+1;
    *str = 0;
    return fillet;
}

char ** filletArguments(char * arguments){
    static char *argsVec[MAX_ARGS + 1]; // +1 for NULL terminator
    static char argsStorage[MAX_ARGS][MAX_ARG_LEN];

    int argIndex = 0;
    int charIndex = 0;

    while (*arguments != '\0' && argIndex < MAX_ARGS) {
        // saltear espacios de mas
        while (*arguments == ' ') {
            arguments++;
        }

        if (*arguments == '\0') {
            break;
        }

        // comienzo de un arguemnto
        charIndex = 0;

        while (*arguments != ' ' && *arguments != '\0' && charIndex < MAX_ARG_LEN - 1) {
            argsStorage[argIndex][charIndex++] = *arguments++;
        }

        argsStorage[argIndex][charIndex] = '\0';         // Nnull terminar el argumentos
        argsVec[argIndex] = argsStorage[argIndex];       // apuntar argsVec a el argumento guardado
        argIndex++;
    }

    argsVec[argIndex] = 0; // Null terminar la lista

    return argsVec;
}

// leer entrada -> dirigir comandos
void entryHandler(char * entry){
    if(*entry == '\n'){
        return;
    }
    
    char f = 0;
    for( int i = 0 ; i < commands_size ; i++){
        if(strcmp(entry, commands[i]) == 0){
            switch(i){
                case 0:
                    f = 0;
                    help();
                return;
                case 1:
                    f = 0;
                    playGolf();
                return;
                case 2:
                    f = 0;
                    time();
                return;
                case 3:
                    f = 0;
                    printRegisters();
                return;
                default:
                return;
            }
        } else {
            f = 1;
        }
    }
    if(f == 1){
        printf("eso no es un comando, hace help xq necesitas ayuda chinchulin\n");
    }
}


void help(){
    printf("no tengo info para proveerte sorry se menos q vos\n");
}

void printRegisters(){
    printf("todavia no se implemento te pido perdon volve mas tarde\n");
}

void time(){
    printf("todavia no se implemento te pido perdon volve mas tarde\n");
}

void clearScreen(){
    syscall_clearScreen();
}

void playGolf(){
    printf("todavia no se implemento te pido perdon volve mas tarde\n");
}

