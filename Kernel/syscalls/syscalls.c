#include <defs.h>
#include <stdint.h>
#include <drivers/keyboardDriver.h>
#include <drivers/videoDriver.h>
#include <interruptions/lib.h>
#include <syscalls/syscalls.h>


uint64_t sysCallDispatcher(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6){
    switch (syscallNumber)
    {
    case READ:
        sys_read(arg1, (char *)arg2, arg3);      // fd, buffer and count
        return 0;
    case WRITE:
        sys_write(arg1, (char*)arg2, arg3);     // fd, buffer and count
        return 0;
    case SOUND:
        sys_sound(arg1, arg2);       // time, frequency
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
        //print("ERROR DE FD")
    }
}

void sys_write(uint64_t fd, char * buffer, uint64_t count){
    if(fd==STDOUT){
    putChar(*buffer, WHITE);
    }else {
        //print("ERROR DE FD")
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