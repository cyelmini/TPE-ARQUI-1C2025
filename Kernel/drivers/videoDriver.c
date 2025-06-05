#include <time.h>
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
    uint16_t attributes;
    uint8_t window_a;
    uint8_t window_b;
    uint16_t granularity;
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;
    uint16_t pitch;
    uint16_t width;
    uint16_t height;
    uint8_t w_char;
    uint8_t y_char;
    uint8_t planes;
    uint8_t bpp;
    uint8_t banks;
    uint8_t memory_model;
    uint8_t bank_size;
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

    uint32_t framebuffer;
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size;
    uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;


// Manejo de píxeles y pantalla

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *)(uintptr_t)VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

void putRectangle(uint64_t x, uint64_t y, uint64_t height, uint64_t width, uint32_t hexColor){
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            putPixel(hexColor, x + i, y + j);
        }
    }
}

void drawCircle(uint64_t x0, uint64_t y0, uint64_t radius, uint64_t color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        putPixel(color, x0 + x, y0 + y);
        putPixel(color, x0 + y, y0 + x);
        putPixel(color, x0 - y, y0 + x);
        putPixel(color, x0 - x, y0 + y);
        putPixel(color, x0 - x, y0 - y);
        putPixel(color, x0 - y, y0 - x);
        putPixel(color, x0 + y, y0 - x);
        putPixel(color, x0 + x, y0 - y);

        y++;
        if (err <= 0) {
            err += 2 * y + 1;
        } else {
            x--;
            err += 2 * (y - x + 1);
        }
    }
}

void clearRectangle(uint64_t x, uint64_t y, uint64_t height, uint64_t width){
    putRectangle(x, y, height, width, BLACK);
}

void clearScreen(){
    putRectangle(0, 0, VBE_mode_info->height, VBE_mode_info->width, BLACK);
    cursor_x = 0;
    cursor_y = 0;
}

void changeBackgroundColor(uint32_t hexColor){
    putRectangle(0, 0, VBE_mode_info->height, VBE_mode_info->width, hexColor);
}


// Manejo del cursor

uint64_t getCursorX(){ 
	return cursor_x / CHAR_WIDTH; 
}

uint64_t getCursorY(){ 
	return cursor_y / CHAR_HEIGHT; 
}

void setCursor(uint64_t x, uint64_t y){ 
	cursor_x = x; 
	cursor_y = y; 
}

void drawCursor(){ 
	putRectangle(cursor_x, cursor_y, CHAR_HEIGHT, CHAR_WIDTH, WHITE); 
}


// Dimensiones de pantalla y caracteres

uint64_t getScreenHeight(){ 
	return VBE_mode_info->height; 
}

uint64_t getScreenWidth(){ 
	return VBE_mode_info->width; 
}

void changeCharSize(int size){ 
	CHAR_HEIGHT += size; 
	CHAR_WIDTH += size; 
	CHAR_SIZE = size; }

void defaultCharSize(){ 
	CHAR_HEIGHT = DEFAULT_HEIGHT; 
	CHAR_WIDTH = DEFAULT_WIDTH; 
	CHAR_SIZE = 1; }

uint64_t getCharHeight(){ return CHAR_HEIGHT; }


// Funciones de impresión

void putChar(char c, uint32_t hexcode){
    switch(c){
        case '\b': putBackspace(); return;
        case '\n': putNewLine(); return;
        case '\t': putTab(); return;
        default: drawChar(c, hexcode); return;
    }
}

void printf(char * str, uint32_t hexcode) {
    int i = 0;
    while(str[i] != '\0'){
        putChar(str[i], hexcode);
        i++;
    }
}

void puts(char * string){
    for(int i = 0 ; string[i] != 0 ; i++){
        putChar(string[i], WHITE);
    }
    putChar('\n', WHITE);
}

void print(const char * string, va_list list){
    for(int i = 0; string[i] != 0 ; i++){
        if(string[i] == '%' && string[i + 1] != 0){
            switch (string[i+1]){
                case 'd': putChar(*numToString(va_arg(list, int)), WHITE); i++; break;
                case 's': puts(va_arg(list, char*)); i++; break;
                case 'c': putChar(va_arg(list, int), WHITE); i++; break;
                default: putChar('%', WHITE); break;
            }
        } else {
            putChar(string[i], WHITE);
        }
    }
}


// Control de caracteres especiales

void drawChar(char c, uint32_t hexcode) {
    clearRectangle(cursor_x, cursor_y, CHAR_HEIGHT, CHAR_WIDTH);
    int start = c - FIRST_CHAR;
    if (c >= FIRST_CHAR && c <= LAST_CHAR) {
        if (cursor_x + CHAR_WIDTH >= VBE_mode_info->width - CHAR_WIDTH) {
            cursor_x = 0;
            cursor_y += CHAR_HEIGHT;
            if (cursor_y / CHAR_HEIGHT >= VBE_mode_info->height / CHAR_HEIGHT) {
                clearScreen();
            }
            return;
        }
        for (int i = 0; i < DEFAULT_HEIGHT; i++) {
            for (int j = 0; j < DEFAULT_WIDTH; j++) {
                if ((uint8_t)font_bitmap[i + ((start) * 32)] & (1 << j)) {
                    putRectangle(cursor_x + j, cursor_y + i, CHAR_SIZE, CHAR_SIZE, hexcode);
                }
            }
        }
        cursor_x += CHAR_WIDTH;
    }
}

void putBackspace() {
	clearRectangle(cursor_x, cursor_y, CHAR_HEIGHT, CHAR_WIDTH);
    if (cursor_x == 0 && cursor_y == 0) return;
    if (cursor_x == 0) {
        clearRectangle(cursor_x, cursor_y, CHAR_HEIGHT, CHAR_WIDTH);
        cursor_y -= CHAR_HEIGHT;
        cursor_x = ((VBE_mode_info->width / CHAR_WIDTH) - 1) * CHAR_WIDTH;
    } else {
        cursor_x -= CHAR_WIDTH;
    }
    clearRectangle(cursor_x, cursor_y, CHAR_HEIGHT, CHAR_WIDTH);
}

void putNewLine(){
    clearRectangle(cursor_x, cursor_y, CHAR_HEIGHT, CHAR_WIDTH);
    cursor_x = 0;
    cursor_y += CHAR_HEIGHT;
    if (cursor_y / CHAR_HEIGHT >= VBE_mode_info->height / CHAR_HEIGHT) {
        clearScreen();
    }
}

void putTab(){
    clearRectangle(cursor_x, cursor_y, CHAR_HEIGHT, CHAR_WIDTH);
    if((cursor_x + TAB * DEFAULT_WIDTH) >= VBE_mode_info->width){
        putNewLine(); return;
    }
    cursor_x += TAB * DEFAULT_WIDTH;
}


// Funciones auxiliares

char * numToString(uint64_t num) {
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
