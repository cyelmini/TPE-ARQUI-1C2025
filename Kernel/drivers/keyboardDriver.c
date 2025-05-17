#include <stdint.h>
#include <keyboardDriver.h>

#define KEYS 58
#define BUFFER_SIZE 512 

// utility keys
#define ESC 0x01
#define BACK 0x0E
#define TAB 0x0F
#define ENTER 0x1C
#define CAPS 0x3A
#define LSHIFT 0x2A
#define RSHIFT 0x36
#define CTRL 0x1D
#define ALT 0x38

#define LSHIFT_RELEASED (LSHIFT + 0x80)
#define RSHIFT_RELEASED (RSHIFT + 0x80)
#define CTRL_RELEASED (CTRL + 0x80) 
#define ALT_RELEASED (ALT + 0x80)

#define TAB_AMOUNT 4

// flags to manage capitalization of letters and special keys
char shift_pressed = 0;
char caps_pressed = 0;
char ctrl_pressed = 0;
char alt_pressed = 0;

// global variables to manage buffer
char buffer[BUFFER_SIZE] = {0}; 
int buffer_index = 0;
int current_char = 0;
int cant_elems = 0;

static unsigned char keyboard[KEYS][2] = {
    {0, 0}, {27, 27}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'},
    {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, 
    {0, 0}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {39, 34}, {'`', '~'},
    {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}, {0, 0},
    {0, 0}, {0, 0}, {' ', ' '},
};

void keyboardHandler(){
    uint64_t scancode_key = getKey(); 

    switch (scancode_key) {
    case RSHIFT:
    case LSHIFT:
        shift_pressed = 1;
        break;
    case LSHIFT_RELEASED:
    case RSHIFT_RELEASED:
        shift_pressed = 0;
        break;
    case CAPS:
        caps_pressed = !caps_pressed;
        break;
    case CTRL:
        ctrl_pressed = 1;
        break;
    case CTRL_RELEASED:
        ctrl_pressed = 0;
        break;
    case ALT:
        alt_pressed = 1;
        break;
    case ALT_RELEASED:
        alt_pressed = 0;
        break;
    case TAB:
        if (cant_elems + TAB_AMOUNT < BUFFER_SIZE) {
            for (int i = 0; i < TAB_AMOUNT; i++) {
                buffer[buffer_index++] = ' ';
                cant_elems++;
            }
        }
        break;
    case ESC:
        break;
    case ENTER:
        if (cant_elems < BUFFER_SIZE) {
            buffer[buffer_index++] = '\n';
            cant_elems++;
        }
        break;
    case BACK:
        if (cant_elems > 0 && buffer_index > 0) {
            buffer_index--;
            cant_elems--;
            buffer[buffer_index] = 0;
        }
        break;
    default:
        if (scancode_key < KEYS && keyboard[scancode_key][0] != 0) {
            if (cant_elems < BUFFER_SIZE) {
                char key = keyboard[(int)scancode_key][(caps_pressed + shift_pressed) % 2];
                buffer[buffer_index++] = key;
                cant_elems++;
            }
        }
        break;
    }
}

char * getBuffer(){
    return buffer;
}

char nextChar(){
    if (cant_elems <= 0) {
        return -1;
    }
    if (current_char == BUFFER_SIZE) {
        current_char = 0;
    }
    cant_elems--;
    return buffer[current_char++];
}
