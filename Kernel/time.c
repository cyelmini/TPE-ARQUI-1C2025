#include <time.h>
#include <interruptions/lib.h>
#include <interruptions/interrupts.h>

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

void sleep_ms(int milliseconds) {
    unsigned long start = ticks;
    // 18 ticks per second = 0.018 ticks per millisecond
    unsigned long wait_ticks = (milliseconds * 18) / 1000;
    
    // Ensure at least 1 tick for small values
    if (wait_ticks == 0 && milliseconds > 0)
        wait_ticks = 1;
        
    while (ticks - start < wait_ticks){
        _hlt();
    }
}