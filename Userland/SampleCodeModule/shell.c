#include "include/libC.h"
#include "include/shell.h"
#include "include/syscalls.h"
#include "include/exceptions.h"
#include "include/pongi_golf/golf.h"

#define BUFFER_SIZE 1024
#define MAX_ARGS 10
#define MAX_ARG_LEN 50

#define PURPLE 0xEE82EE
#define USER_COLOR 0x00FFF0

/**
 * @brief Convierte un valor en formato BCD (Binary-Coded Decimal) a formato binario
 * @param bcd El valor en formato BCD que se desea convertir
 * @return El valor convertido a formato binario
 */
static int bcdToBinary(int bcd);

/**
 * @brief Limpia un buffer estableciendo todos sus elementos a cero
 * @param buffer Puntero al buffer que se desea limpiar
 */
static void clearBuffer(char * buffer);

/**
 * @brief Genera una excepción de operación inválida
 */
static void invalidOpException();

/**
 * @brief Genera una excepción de división por cero
 */
static void divisionByZeroException();


void initializeShell(){
    printf("Bienvenido al mejor sistema operativo del mundo. Ingrese help para conocer los comandos disponibles.\n");
    scanEntry();
}

void scanEntry() {
    char buffer[BUFFER_SIZE] = {0};
    while(1){    
        printColor("$USER@", USER_COLOR);
        printColor(":/path/path$ ", PURPLE);

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

/* ---------------------------------- Command Functions ------------------------------------- */

void executeCommand(char * command, char * arg){
   
    if(strcmp(command, "help") == 0) {
        help(arg);
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
        initializeGolf();
        return;
    } else if (strcmp(command, "invalidOp") == 0) {
        invalidOpException();
        return;
    } else if (strcmp(command, "divisionByZero") == 0) {
        divisionByZeroException();
        return;
    } else if(strcmp(command, "fontUp") == 0) {
        syscall_changeCharSize(2);
        return;
    } else if(strcmp(command, "fontDown") == 0) {
       syscall_changeCharSize(-2);
        return;
    }else if(strcmp(command, "fontDefault") == 0) {
        syscall_defaultCharSize();
        return;
    }
    
    printf("El comando '%s' no es valido\n", command);
    printf("Escribe 'help' para conocer la lista de comandos disponibles.\n");
}

void help(char *command){

    if(command[0] == 0) {
        printf("==== COMANDOS DISPONIBLES ====\n");
        
        printf(" - help\n");
        printf(" - time\n");
        printf(" - printRegisters\n");
        printf(" - clear\n");  
        printf(" - playGolf\n");
        printf(" - invalidOp\n");
        printf(" - divisionByZero\n");
        printf(" - fontUp\n");
        printf(" - forntDown\n");
        printf(" - fontDefault\n");

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

    } else if(strcmp(command, "invalidOp") == 0) {

        printf("Comando: invalidOp\n");
        printf("Lanza una excepcion por operacion invalida\n");

    } else if(strcmp(command, "divisionByZero") == 0) {

        printf("Comando: divisionByZero\n");
        printf("Lanza una excepcion por division por cero\n");

    } else if(strcmp(command, "fontUp") == 0) {

        printf("Comando: fontUp\n");
        printf("Aumenta el tamaño de la letra\n");

    } else if(strcmp(command, "fontDown") == 0) {

        printf("Comando: fontDown\n");
        printf("Disminuye el tamaño de la letra\n");

    } else if(strcmp(command, "fontDefault") == 0) {

        printf("Comando: fontDefault\n");
        printf("Restablece el tamaño de la letra al valor por defecto\n");

    } else {
        printf("El comando '%s' no es valido\n", command);
    }
}

void printRegisters(){
    syscall_getRegisters();
}

void time(){
    int hours = bcdToBinary(getHoursUser()) - 3;
    if (hours < 0) {
        hours += 24;  // Ajustar para valores negativos en el formato de 24 horas
    }
    int minutes = bcdToBinary(getMinutesUser());
    int seconds = bcdToBinary(getSecondsUser());

    printf("Hora actual: %d:%d:%d\n", hours, minutes, seconds);
}

static void invalidOpException() {
    invalidOpCode();
    return;
}

static void divisionByZeroException() {
    divisionByZero();
    return;
}

/* --------------------------------- Auxiliar Functions ------------------------------------ */

static int bcdToBinary(int bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

void clearScreen(){
    syscall_clearScreen();
}

void clearBuffer(char * buffer){
    for(int i = 0; i < BUFFER_SIZE; i++){
        buffer[i] = 0;
    }
}
