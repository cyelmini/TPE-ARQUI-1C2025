#include <defs.h>
#include <stdint.h>
#include <keyboardDriver.h>
#include <videoDriver.h>

#define STDIN 0
#define STDOUT 1
#define STERR 2

#define READ 0
#define WRITE 1
#define OPEN 2
#define CLOSE 3
#define SOUND 4
#define SECONDS 5
#define MINUTES 6
#define HOURS 7


uint64_t sysCallDispatcher(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6){
    switch (syscallNumber)
    {
    case READ:
        sys_read(arg1, (char *)arg2, arg3);      // fd, buffer and count
        return 0;
    case WRITE:
        sys_write(arg1, (char*)arg2, arg3);     // fd, buffer and count
        return 0;
    case OPEN:
        sys_open((char *)arg1, arg2, arg3);     // filename, flags, mode 
        return 0;
    case CLOSE: 
        sys_close(arg1);        // fd
        return 0;
    case SOUND:
        sys_sound(arg1, arg2);      // time, frequency
    case SECONDS:
        sys_seconds(arg1);          // seconds
        return 0;
    case MINUTES:
        sys_minutes(arg1);        // minutes
        return 0;
    case HOURS:
        sys_hours(arg1);       // hours
        return 0;
    default:
        return -1; 
    }
}

void sys_read(uint64_t fd, char * buffer, uint64_t count){
    if(fd == STDIN){
        for(int i; i < count; i++){ // mejor q sea un while
            char caracter = nextChar();
            if (caracter == -1){
                return;
            }
            *buffer = caracter;
            buffer++;
        }
    } else{
        //print("ERROR DE FD")
    }
}

void sys_write(uint64_t fd, char * buffer, uint64_t count){
    putChar(*buffer, WHITE);
}