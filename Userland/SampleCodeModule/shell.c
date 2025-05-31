#include "include/libC.h"
#include "include/shell.h"
#include "include/syscalls.h"

#define BUFFER_SIZE 1024
#define MAX_ARGS 10
#define MAX_ARG_LEN 50

static char * commands[] = {"help", "time", "printRegisters", "playGolf"};
static int commands_size = 4; 


static void clearBuffer(char * buffer);
static void clearScreen();


void initializeShell(){
    printf("Bienvenido al mejor sistema operativo en el universo.\n");
    printf("Ingrese 'help' para conocer los comandos disponibles, o 'help $COMMAND' para saber mas sobre un comando.\n\n");
    scanEntry();
    
}

void scanEntry() {
    char buffer[BUFFER_SIZE] = {0};

    while(1){    
        printf("$USER@$DEVICE_NAME:/path/path$ ");

        int len = scanf(buffer);

        if (len > 0 && buffer[0] != '\n') {
            entryHandler(buffer);
        }

        clearBuffer(buffer);
    }
}

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

/* ---------------------------------- command functions ------------------------------------- */

void help(){
    printf("no tengo info para proveerte sorry se menos q vos\n");
}

void printRegisters(){
    printAllRegisters();
}

>>>>>>> papa
void time(){
    printf("La hora actual es: %d:0%d:0%d\n", getHours(), getMinutes(), getSeconds());
}


void playGolf(){
    printf("todavia no se implemento te pido perdon volve mas tarde\n");
}


/* --------------------------------- auxiliar functions ------------------------------------ */

void clearScreen(){
    syscall_clearScreen();
}

void clearBuffer(char * buffer){
    for(int i = 0; i < BUFFER_SIZE; i++){
        buffer[i] = 0;
    }
}

