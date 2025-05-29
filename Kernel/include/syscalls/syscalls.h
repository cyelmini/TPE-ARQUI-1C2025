#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STERR 2


uint64_t sysCallDispatcher(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6);
void sys_read(uint64_t fd, char * buffer, uint64_t count);
void sys_write(uint64_t fd, char * buffer, uint64_t count);
void sys_seconds(uint64_t *seconds);
void sys_minutes(uint64_t *minutes);
void sys_hours(uint64_t *hours);
void sys_sound(uint64_t time, uint64_t frequency);
void sys_getRegisters(uint64_t * registers);

#endif