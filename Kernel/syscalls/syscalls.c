#include <defs.h>
#include <stdint.h>
#include <drivers/keyboardDriver.h>
#include <drivers/videoDriver.h>
#include <interruptions/lib.h>
#include <syscalls/syscalls.h>
#include <time.h>
#include <interruptions/interrupts.h>

#define READ 0
#define WRITE 1
#define SECONDS 2
#define MINUTES 3
#define HOURS 4
#define SOUND 5
#define SET_CURSOR 6
#define GET_CURSOR_X 7
#define GET_CURSOR_Y 8
#define DRAW_CURSOR 9
#define GET_SCREEN_HEIGHT 10
#define GET_SCREEN_WIDTH 11
#define GET_REGISTERS 12
#define CLEAR_SCREEN 13
#define CHANGE_CHAR_SIZE 14
#define DEFAULT_CHAR_SIZE 15
#define CHANGE_BACKGROUND_COLOR 16
#define COLOR_WRITE 17
#define PUT_RECTANGLE 18
#define DRAW_CIRCLE 19
#define SLEEP 20

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
        setCursor(arg1, arg2);
        return 0;
   
        case GET_CURSOR_X:
        return getCursorX();     
    
        case GET_CURSOR_Y:
        return getCursorY();       

        case DRAW_CURSOR:
        drawCursor();
        return 0;
    
        case GET_SCREEN_HEIGHT:
        return getScreenHeight();

        case GET_SCREEN_WIDTH:
        return getScreenWidth();

        case GET_REGISTERS:
        printRegs();
        return 0;

        case CLEAR_SCREEN:
        clearScreen();
        return 0;

        case CHANGE_CHAR_SIZE:
        changeCharSize(arg1);
        return 0;

        case DEFAULT_CHAR_SIZE:
        defaultCharSize();
        return 0;

        case CHANGE_BACKGROUND_COLOR:
        changeBackgroundColor(arg1);
        
        case COLOR_WRITE:
        putChar(*(char *)arg1, arg2); 
        return 0;

        case PUT_RECTANGLE:
        putRectangle(arg1, arg2, arg3, arg4, arg5);
        return 0;

        case DRAW_CIRCLE:
        drawCircle(arg1, arg2, arg3, arg4);
        return 0;
        
        case SLEEP:
        sleep(arg1);
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
