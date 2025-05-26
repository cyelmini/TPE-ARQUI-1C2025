#include <time.h>
#include <interruptions/lib.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}


void sleep(int seconds) {
	unsigned long start = ticks;
	while (ticks - start < seconds * 18){
		_hlt();
	}
}