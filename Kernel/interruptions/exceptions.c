#include <kernelLib.h>
#include <drivers/videoDriver.h>
#include <interruptions/interrupts.h>
#include <defs.h>


#define ZERO_EXCEPTION_ID 0

static void zero_division();
static void invalidOpCode();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
	} else {
		invalidOpCode();
	}
	return;
}

static void zero_division() {
	printf("Excepcion: Division por cero\n", WHITE);
	snapShotFlag = 1;
	printRegs();
	return;
}

static void invalidOpCode() {
	printf("Excepcion: Codigo de operacion invalido\n", WHITE);
	snapShotFlag = 1;
	printRegs();
	return;
}