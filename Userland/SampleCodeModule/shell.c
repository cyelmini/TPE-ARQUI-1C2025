#include "include/libC.h"
#include "include/shell.h"
#include "include/syscalls.h"
#include "include/exceptions.h"

#define BUFFER_SIZE 1024
#define MAX_ARGS 10
#define MAX_ARG_LEN 50

static void clearBuffer(char * buffer);
static void clearScreen();
static void executeCommand();

/*------------------------Funciones nuevas-------------------------------------*/

static void invalidOpException();
static void divisionByZeroException();

static void invalidOpException() {
    printf("Error: Operacion invalida.\n");
    invalidOpCode();
}

static void divisionByZeroException() {
    printf("Error: Division por cero.\n");
    divisionByZero();
}
/*-----------------------------------------------------------------------------*/


void initializeShell(){
    // FALTA ARREGLAR IMPRESION Y BACKSPACE
    printf("Bienvenido al mejor sistema operativo del mundo. Ingrese help para conocer los comandos disponibles.\n");
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
    
    char command[BUFFER_SIZE] = {0};
    char arg[BUFFER_SIZE] = {0}; 
    
    
    int i = 0;
    int j = 0;

    // buscamos el comando hasta el espacio 
    while(entry[i] != ' ' && entry[i] != 0) {
        command[i] = entry[i];
        i++;
    }
    command[i] = 0;
    
    // buscamos el argumento 
    if(entry[i] == ' ') {
        i++; // Saltar el espacio
        while(entry[i] != 0) {
            arg[j] = entry[i];
            i++;
            j++;
        }
        arg[j] = 0;
    }

    executeCommand(command, arg);
}

/* ---------------------------------- command functions ------------------------------------- */

void executeCommand(char * command, char * arg){
   
    if(strcmp(command, "help") == 0) {
        help(arg);
        return;
    } else if(strcmp(command, "time") == 0) {
        time();
        return;
    } else if(strcmp(command, "printRegisters") == 0) {
        printRegisters();
        return;
    } else if(strcmp(command, "clear") == 0) {
        clearScreen();
        return;
    } else if(strcmp(command, "playGolf") == 0) {
        playGolf();
        return;
        /*--------------------------Nuevo------------------------------*/
    } else if (strcmp(command, "invalidOp") == 0) {
        invalidOpException();
        return;
    } else if (strcmp(command, "divisionByZero") == 0) {
        divisionByZeroException();
        return;
    }
        /*-------------------------------------------------------------*/
    printf("El comando '%s' no es valido\n", command);
    printf("Escribe 'help' para conocer la lista de comandos disponibles.\n");
}

// FALTA DIVIDEBYCERO E INVALIDOP (no se si alguno mas)

void help(char *command){

    if(command[0] == 0) {
        printf("==== COMANDOS DISPONIBLES ====\n");
        
        printf(" - help\n");
        printf(" - time\n");
        printf(" - printRegisters\n");
        printf(" - clear\n");  
        printf(" - playGolf\n");

        printf("Para conocer mas informacion sobre un comando especifico, escribe 'help + comando'.\n");

    } else if(strcmp(command, "help") == 0) {

        printf("Comando: help [comando]\n");
        printf("Sin argumentos, muestra la lista de comandos disponibles.\n");
        printf("Con un comando como argumento, muestra informacion detallada sobre ese comando.\n");

    } else if(strcmp(command, "time") == 0) {

        printf("Comando: time\n");
        printf("Muestra la hora actual del sistema en formato HH:MM:SS\n");

    } else if(strcmp(command, "printRegisters") == 0) {

        printf("Comando: printRegisters\n");
        printf("Muestra los valores actuales de todos los registros del CPU\n");

    } else if(strcmp(command, "clear") == 0) {  
        
        printf("Comando: clear\n");
        printf("Limpia la pantalla y reinicia la posicion del cursor\n");

    } else if(strcmp(command, "playGolf") == 0) {

        printf("Comando: playGolf\n");
        printf("Inicializa una partida de golf\n");

    } else {
        printf("El comando '%s' no es valido\n", command);
    }
}

// REVISAR
void printRegisters(){
    syscall_getRegisters();
}

// REVISAR 
void time(){
    printf("La hora actual es: %d:0%d:0%d\n", getHours(), getMinutes(), getSeconds());
}

//FALTA
void playGolf(){
    printf("Falta implementar\n");
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

