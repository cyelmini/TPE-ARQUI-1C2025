extern void syscall_read(int fd, char * buffer, int count);

extern void syscall_write(int fd, const char * buffer, int count);

extern void syscall_seconds(int * seconds);

extern void syscall_minutes(int * minutes);

extern void syscall_hours(int * hours);

extern void syscall_sound(int time, int frequency);

extern void syscall_setCursorX(int x);

extern void syscall_setCursorY(int y);

extern int syscall_cursorX();

extern int syscall_cursorY();