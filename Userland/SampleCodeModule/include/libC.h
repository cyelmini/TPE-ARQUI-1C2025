#include <stdarg.h>
#include "user_syscalls.h"


void putChar(char c, int fd);

void puts(char * string);

void printf(const char * string, ...);