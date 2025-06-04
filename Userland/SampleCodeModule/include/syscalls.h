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

extern int syscall_drawCursor();

extern int syscall_getScreenHeight();

extern int syscall_getScreenWidth();

extern int syscall_getRegisters();

extern void syscall_clearScreen();

extern void syscall_changeCharSize();

extern void syscall_defaultCharSize();

extern void syscall_changeBackgroundColor(int color);

extern void syscall_colorWrite(char * c, int color);

extern void syscall_putRectangle(int x, int y, int height, int width, int color);

extern void syscall_drawCircle(int x, int y, int radius, int color);

extern void syscall_sleep(int seconds);