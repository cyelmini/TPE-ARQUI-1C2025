#include <defs.h>
#include <font.h>
#include <stdarg.h>
#include <drivers/videoDriver.h>
#include <drivers/keyboardDriver.h>

#define DEFAULT_HEIGHT 32
#define DEFAULT_WIDTH 10

#define FIRST_CHAR 32
#define LAST_CHAR 126

#define TAB 4

static int CHAR_SIZE = 1;
static int CHAR_HEIGHT = DEFAULT_HEIGHT;
static int CHAR_WIDTH = DEFAULT_WIDTH;

uint64_t cursor_x = 0;
uint64_t cursor_y = 0;

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;				// number of bytes per horizontal line
	uint16_t width;				// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;				// unused...
	uint8_t y_char;				// ...
	uint8_t planes;
	uint8_t bpp;				// bits per pixel in this mode
	uint8_t banks;				// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;			// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;			// physical address of the linear frame buffer, write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *)(uintptr_t)VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

uint64_t getCursorX(){
	return cursor_x;
}

uint64_t getCursorY(){
	return cursor_y;
}

void setCursorX(uint64_t x){
	if(x >= VBE_mode_info->width || x < 0){
		return; // cursor is out of screen bounds
	}
	cursor_x = x;
}

void setCursorY(uint64_t y){
	if(y >= VBE_mode_info->height || y < 0){
		return; // cursor is out of screen bounds
	}
	cursor_y = y;
}

void setCursor(uint64_t x, uint64_t y){
	cursor_x = x;
	cursor_y = y;
}


void putChar(char c, int hexcode){
//	char * buffer = getBuffer();
	switch(c){
		case '\b':
			putBackspace();
		return;
		case '\n':
			putNewLine();
		return;
		case '\t':
			putTab();
		return;
		default:
			drawChar(c, hexcode);
		return;
	}
}
/*
void printf(char * str, uint32_t hexcode) {
	int i = 0;
	while(str[i] != '\0'){
		putChar(str[i], hexcode);
		i++;
	}
}*/

void putBackspace() {
	// if the cursor is on the first position of the screen (top left corner)
    if (cursor_x == 0 && cursor_y == 0) {
        return;
    }

    // if the cursor is at the beggining of a line, we move it to the end of the
	// last line and delete the character on that line 
    if (cursor_x == 0 && cursor_y >= CHAR_HEIGHT) {
        cursor_y -= CHAR_HEIGHT;
        cursor_x = ((VBE_mode_info->width / CHAR_WIDTH) - 1) * CHAR_WIDTH;
    } else {
        cursor_x -= CHAR_WIDTH; // just move backwards one position
    }

    // delete the character in the cursors new position 
    clearRectangle(cursor_x, cursor_y, CHAR_HEIGHT, CHAR_WIDTH);
}

void putNewLine(){
	setCursor(0, (uint64_t)getCursorY() + DEFAULT_HEIGHT);
}

void putTab(){
	if((cursor_x + TAB * DEFAULT_WIDTH) >= VBE_mode_info->width){
			putNewLine(); 	// if we exceed the screen's width we continue writing on the next line
			return;
		}
	cursor_x += TAB * DEFAULT_WIDTH;
}

void drawChar(char c, uint64_t hexcode){
	int start = c - FIRST_CHAR;
    if (c >= FIRST_CHAR && c <= LAST_CHAR) {
    	if (cursor_x + CHAR_WIDTH >= VBE_mode_info->width) {
            putNewLine();
        }
    	// Draw the character
        for (int i = 0; i < DEFAULT_HEIGHT ; i++) {
            for (int j = 0; j < DEFAULT_WIDTH; j++) {
                // Change the order of the bits
                if ((uint8_t)font_bitmap[i + ((start) * 32)] & (1 << j)) {
					putRectangle(cursor_x + j, cursor_y + i, CHAR_SIZE, CHAR_SIZE, hexcode);   	
             	}
            }
        }
        // Increment cursor position
        cursor_x += CHAR_WIDTH;
        }
    return;
}

void clearRectangle(int x, int y, int height, int width){
	putRectangle(x, y, height, width, BLACK);
}

void putRectangle(int x, int y, int height, int width, uint32_t hexColor){
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			putPixel(hexColor, x + i, y + j);
		}
	}
}


char * numToString(int num) {
    static char buffer[21]; 
    char *ptr = buffer + sizeof(buffer) - 1;
    unsigned long long n;
    int isNegative = 0;

    *ptr = '\0';

    if (num == 0) {
        *(--ptr) = '0';
        return ptr;
    }

    if (num < 0) {
        isNegative = 1;
        n = (unsigned long long)(-(long long)num);
    } else {
        n = (unsigned long long)num;
    }

    while (n != 0) {
        *(--ptr) = (n % 10) + '0';
        n /= 10;
    }

    if (isNegative)
        *(--ptr) = '-';

    return ptr;
}

void puts(char * string){
    for(int i = 0 ; string[i] != 0 ; i++){
        putChar(string[i], WHITE);
    }
    putChar('\n', WHITE);
}

void print(const char * string, va_list list);
void print(const char * string, va_list list){
    for(int i = 0; string[i] != 0 ; i++){
        if(string[i] == '%' && string[i + 1] != 0){
            switch (string[i+1]){
                case 'd':
                    putChar(*numToString(va_arg(list, int)), WHITE);
					i++;
                break;
                case 's':
                    puts(va_arg(list, char*));
					i++;
                break;
                case 'c':
                    putChar(va_arg(list, int), WHITE);
					i++;
                break;
                default:
                    putChar('%', WHITE);
                break;
            }
        } else {
            putChar(string[i], WHITE);
        }
    }
}

void printf(const char * string, ...){
    va_list list;
    va_start(list, string);
    print(string, list);
    va_end(list);
}

void changeSize(int size){
	CHAR_HEIGHT += size;
	CHAR_WIDTH += size ;
	CHAR_SIZE = size;
}