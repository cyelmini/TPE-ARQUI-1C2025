#include <defs.h>
#include <stdint.h>
#include <drivers/keyboardDriver.h>
#include <drivers/videoDriver.h>
#include <interruptions/lib.h>
#include <syscalls/syscalls.h>
#include <time.h>

#define READ 0
#define WRITE 1
#define SECONDS 2
#define MINUTES 3
#define HOURS 4
#define SOUND 5
#define SET_CURSOR 6
#define GET_CURSOR_X 7
#define GET_CURSOR_Y 8
#define CURSOR 9
#define GET_SCREEN_HEIGHT 10
#define GET_REGISTERS 11
#define CLEAR_SCREEN 12

extern uint64_t registers[18]; // 18 son la cant de registros que se guardan 


uint64_t sysCallDispatcher(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6){
    switch (syscallNumber)
    {
        case READ:
        sys_read(arg1, (char *)arg2, arg3);      // fd, buffer and count
        return 0;
    
        case WRITE:
        sys_write(arg1, (char*)arg2, arg3);     // fd, buffer and count
        return 0;
   
        case SECONDS:
        sys_seconds((uint64_t *)arg1);          // seconds
        return 0;
   
        case MINUTES:
        sys_minutes((uint64_t *)arg1);        // minutes
        return 0;
    
        case HOURS:
        sys_hours((uint64_t *)arg1);       // hours
        return 0;
    
        case SOUND:
        sys_sound(arg1, arg2);       // time, frequency
        return 0;

        case SET_CURSOR:
        setCursor(arg1, arg2);       // x, y
        return 0;
   
        case GET_CURSOR_X:
        return getCursorX();       // x
    
        case GET_CURSOR_Y:
        return getCursorY();       // y

        case CURSOR:
        sys_cursor();
        return 0;
    
        case GET_SCREEN_HEIGHT:
        return getScreenHeight();

        case GET_REGISTERS:
        sys_getRegisters((uint64_t *)arg1);       // get registers
        return 0;

        case CLEAR_SCREEN:
        clearScreen();
        return 0;
        
        default:
        return -1; 
    }
}

void sys_read(uint64_t fd, char * buffer, uint64_t count){
    if(fd == STDIN){
        while(count > 0){
            char caracter = nextChar();
            if (caracter == -1){
                return;
            }
            *buffer = caracter;
            buffer++;
            count--;
        }
    } else{
       printf("File Descriptor Error", WHITE);
    }
}

void sys_write(uint64_t fd, char * buffer, uint64_t count){
    if(fd==STDOUT){
        while(count > 0 && *buffer != 0){
            putChar(*buffer, WHITE);
            count--;
            buffer++;
        }
    } else {
        printf("File Descriptor Error", WHITE);
    }
}

void sys_seconds(uint64_t *seconds){
    *seconds = getSeconds();
}

void sys_minutes(uint64_t *minutes){
    *minutes = getMinutes();
}

void sys_hours(uint64_t *hours){
    *hours = getHours();
}

void sys_sound(uint64_t time, uint64_t frequency){
    if (frequency <= 0 || time < 0)
        return;
    
    makeSound(frequency);
    sleep(time);
    stopSound();
}

void sys_getRegisters(uint64_t vec[18]){
    for(int i = 0; i < 18 ; i++){
        vec[i] = registers[i];
    }
 }

void sys_cursor(){
    drawCursor();
}
