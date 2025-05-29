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
    printf("Bienvenido a sistema operativo sin nombre.\nIngrese 'help' para conocer los comandos disponibles, o 'help $COMMAND para saber más sobre un comando.\n");
    while(1){
        printf("$USER@$DEVICE_NAME:/path/path$ ");
        scanEntry();
    }
}

void scanEntry(){
    char buffer[BUFFER_SIZE] = {0};
    
    while(1){
        scanf(buffer);
       
        if(buffer[0] == '\n') { 
            return;                  
        }

        entryHandler(buffer);

        // if(syscall_getCursorY() > syscall_getScreenHeight() - 1){
        //     clearScreen();
        // }

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
    
    char * arguments = filletEntry(entry);
    char ** argsVec = filletArguments(arguments);
    
    for( int i = 0 ; i < commands_size ; i++){
        if(strcmp(entry, commands[i]) == 0){
            switch(i){
                case 0:
                    help(argsVec);
                break;
                case 1:
                    playGolf();
                break;
                case 2:
                    time();
                break;
                case 3:
                    printRegisters();
                break;
                default:
                    printf("eso no es un comando chichulin\n");
                break;
            }
        }
    }
}


void help(char ** args){
    printf("no tengo info para proveerte sorry se menos q vos\n");
}

void printRegisters(){
    printf("todavia no se implemento te pido perdon volve mas tarde\n");
}

void time(){
    
}

// void clearScreen(){
//     syscall_clearScreen();
// }

void playGolf(){
    printf("todavia no se implemento te pido perdon volve mas tarde\n");
}

