/* sampleCodeModule.c */
#include "include/shell.h"
#include "include/libC.h"
#include "include/syscalls.h"

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

int main() {
	initializeShell();

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}