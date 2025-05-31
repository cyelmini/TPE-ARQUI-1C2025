#include <stdint.h>

extern void syscall_read(int fd, char * buffer, int count);

extern void syscall_write(int fd, const char * buffer, int count);

extern void syscall_seconds(uint64_t * seconds);

extern void syscall_minutes(uint64_t * minutes);

extern void syscall_hours(uint64_t * hours);

extern void syscall_sound(int time, int frequency);

extern void syscall_setCursor(int x);

extern int syscall_getCursorX();

extern int syscall_getCursorY();

extern int syscall_cursor();

extern int syscall_getScreenHeight();

extern int syscall_getRegisters(uint64_t * registros);

extern void syscall_clearScreen();

 