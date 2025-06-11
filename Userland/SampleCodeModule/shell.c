#include "include/libC.h"
#include "include/shell.h"
#include "include/syscalls.h"
#include "include/exceptions.h"
#include "include/pongi_golf/golf.h"

#define BUFFER_SIZE 1024
#define MAX_ARGS 10
#define MAX_ARG_LEN 50

#define USER_BLUE  0x0077B6
#define USER_GREEN 0x38DB96

/**
 * @brief Convierte un número en formato BCD (Binary-Coded Decimal) a binario.
 * 
 * @param bcd Número en formato BCD.
 * @return int Número en formato binario.
 */
static int bcdToBinary(int bcd);

/**
 * @brief Limpia el contenido de un buffer.
 * 
 * @param buffer Arreglo de caracteres a limpiar.
 */
static void clearBuffer(char * buffer);

/**
 * @brief Lanza una excepción por operación inválida.
 */
static void invalidOpException();

/**
 * @brief Lanza una excepción por división por cero.
 */
static void divisionByZeroException();

// ---- Inicio de la shell ----

void initializeShell(){
    printf("Bienvenido al mejor sistema operativo del mundo :)\nIngrese 'help' para conocer los comandos disponibles.\n");
    scanEntry();
}

// ---- Lectura del comando ingresado ----

void scanEntry() {
    char buffer[BUFFER_SIZE] = {0};

    while(1){    
        printColor("$USER@:", USER_GREEN);
        printColor("/path/path$ ", USER_BLUE);

        int len = scanf(buffer);

        if (len > 0 && buffer[0] != '\n') {
            entryHandler(buffer);
        }

        clearBuffer(buffer);
    }
}

// ---- Procesamiento del comando y argumento ----

void entryHandler(char * entry){
    if (*entry == '\n') {
        return;
    }
    
    char command[BUFFER_SIZE] = {0};
    char arg[BUFFER_SIZE] = {0}; 
    
    int i = 0;
    int j = 0;

    // Extrae el comando (hasta el primer espacio)
    while (entry[i] != ' ' && entry[i] != 0) {
        command[i] = entry[i];
        i++;
    }
    command[i] = 0;

    // Extrae el argumento (si existe)
    if (entry[i] == ' ') {
        i++; // salta el espacio
        while (entry[i] != 0) {
            arg[j] = entry[i];
            i++;
            j++;
        }
        arg[j] = 0;
    }

    executeCommand(command, arg);
}

// ---- Ejecución del comando correspondiente ----

void executeCommand(char * command, char * arg){
    if (strcmp(command, "help") == 0) {
        help(arg);
    } else if (strcmp(command, "time") == 0) {
        time();
        return;
    } else if (strcmp(command, "printRegisters") == 0) {
        printRegisters();
        return;
    } else if (strcmp(command, "clear") == 0) {
        clearScreen();
        return;
    } else if (strcmp(command, "playGolf") == 0) {
        initializeGolf();
        return;
    } else if (strcmp(command, "invalidOp") == 0) {
        invalidOpException();
        return;
    } else if (strcmp(command, "divisionByZero") == 0) {
        divisionByZeroException();
        return;
    } else if (strcmp(command, "fontUp") == 0) {
        syscall_changeCharSize(2);
        return;
    } else if (strcmp(command, "fontDown") == 0) {
        syscall_changeCharSize(-2);
        return;
    } else if (strcmp(command, "fontDefault") == 0) {
        syscall_defaultCharSize();
        return;
    } else {
        printf("El comando '%s' no es valido\n", command);
        printf("Ingrese 'help' para conocer la lista de comandos disponibles.\n");
    }
}

// ---- Ayuda sobre comandos ----

void help(char *command){
    if (command[0] == 0) {
        printf("==== COMANDOS DISPONIBLES ====\n");
        
        printf(" - help\n");
        printf(" - time\n");
        printf(" - printRegisters\n");
        printf(" - clear\n");  
        printf(" - playGolf\n");
        printf(" - invalidOp\n");
        printf(" - divisionByZero\n");
        printf(" - fontUp\n");
        printf(" - fontDown\n");
        printf(" - fontDefault\n");

        printf("Para conocer mas informacion sobre un comando especifico, escribe 'help <comando>'.\n");

    } else if (strcmp(command, "help") == 0) {
        printf("Comando: help [comando]\n");
        printf("Muestra todos los comandos disponibles o la descripcion de uno especifico.\n");

    } else if (strcmp(command, "time") == 0) {
        printf("Comando: time\n");
        printf("Muestra la hora actual del sistema en formato HH:MM:SS.\n");

    } else if (strcmp(command, "printRegisters") == 0) {
        printf("Comando: printRegisters\n");
        printf("Muestra los valores actuales de todos los registros de la CPU.\n");

    } else if (strcmp(command, "clear") == 0) {  
        printf("Comando: clear\n");
        printf("Limpia la pantalla.\n");

    } else if (strcmp(command, "playGolf") == 0) {
        printf("Comando: playGolf\n");
        printf("Inicia una partida de Pongi Golf.\n");

    } else if (strcmp(command, "invalidOp") == 0) {
        printf("Comando: invalidOp\n");
        printf("Genera una excepcion por operacion invalida.\n");

    } else if (strcmp(command, "divisionByZero") == 0) {
        printf("Comando: divisionByZero\n");
        printf("Genera una excepcion por division por cero.\n");

    } else if (strcmp(command, "fontUp") == 0) {
        printf("Comando: fontUp\n");
        printf("Aumenta la medida de la fuente.\n");

    } else if (strcmp(command, "fontDown") == 0) {
        printf("Comando: fontDown\n");
        printf("Disminuye la medida de la fuente.\n");

    } else if (strcmp(command, "fontDefault") == 0) {
        printf("Comando: fontDefault\n");
        printf("Restablece la medida de la fuente al valor por defecto.\n");

    } else {
        printf("El comando '%s' no es valido.\n", command);
    }
}

// ---- Funciones de comandos del sistema ----

void printRegisters(){
    syscall_getRegisters();
}

void time(){
    int hours = bcdToBinary(getHoursUser()) - 3;
    if (hours < 0) {
        hours += 24;
    }

    int minutes = bcdToBinary(getMinutesUser());
    int seconds = bcdToBinary(getSecondsUser());

    printf("Hora actual: %d:%d:%d\n", hours, minutes, seconds);
}

static void invalidOpException() {
    invalidOpCode();
}

static void divisionByZeroException() {
    divisionByZero();
}

// ---- Funciones auxiliares ----

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
