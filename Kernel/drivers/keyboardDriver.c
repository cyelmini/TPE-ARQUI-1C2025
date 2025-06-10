#include <drivers/keyboardDriver.h>
#include <kernelLib.h>

#define KEYS 58
#define BUFFER_SIZE 1024

// --- Teclas de utilidad ---
#define ESC 0x01
#define BACK 0x0E
#define TAB 0x0F
#define ENTER 0x1C
#define CAPS 0x3A
#define LSHIFT 0x2A
#define RSHIFT 0x36
#define CTRL 0x1D
#define ALT 0x38

#define KEYRELEASE 0x80
#define LSHIFT_RELEASED (LSHIFT + KEYRELEASE)
#define RSHIFT_RELEASED (RSHIFT + KEYRELEASE)
#define CTRL_RELEASED (CTRL + KEYRELEASE) 
#define ALT_RELEASED (ALT + KEYRELEASE)

#define TAB_AMOUNT 4

// --- Variables globales ---
char shift_pressed = 0;
char caps_pressed = 0;
char ctrl_pressed = 0;
char alt_pressed = 0;

char buffer[BUFFER_SIZE] = {0}; 
int write_index = 0;
int read_index = 0;
int remaining_chars = 0;
char getKeyPressed[KEYS] = {0};
int inGameMode = 0;

// --- Tabla de traducción de scancodes ---
static unsigned char keyboard[KEYS][2] = {
    {0, 0}, {27, 27}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'},
    {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, 
    {0, 0}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {39, 34}, {'`', '~'},
    {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}, {0, 0},
    {0, 0}, {0, 0}, {' ', ' '},
};

// --- Funciones principales ---

void keyboardHandler() {
    uint64_t scancode_key = getKey(); 

    if (scancode_key & KEYRELEASE) {
        int released = scancode_key & 0x7F;
        if (released < KEYS) {
            getKeyPressed[released] = 0;
        }
        switch (scancode_key) {
            case LSHIFT_RELEASED:
            case RSHIFT_RELEASED:
                shift_pressed = 0;
                break;
            case CTRL_RELEASED:
                ctrl_pressed = 0;
                break;
            case ALT_RELEASED:
                alt_pressed = 0;
                break;
        }
        return;
    } else {
        if (scancode_key < KEYS) {
            getKeyPressed[scancode_key] = 1;
        }
        switch (scancode_key) {
            case RSHIFT:
            case LSHIFT:
                shift_pressed = 1;
                break;
            case CAPS:
                caps_pressed = !caps_pressed;
                break;
            case CTRL:
                ctrl_pressed = 1;
                break;
            case ALT:
                alt_pressed = 1;
                break;
            case ESC:
                break;
            default:
                if (ctrl_pressed && scancode_key == 0x13) { // ctrl + 'r'
                    snapShotFlag = 1;
                } 
                else if (!inGameMode && scancode_key < KEYS && keyboard[scancode_key][0] != 0 && remaining_chars < BUFFER_SIZE) {
                    char key = keyboard[scancode_key][(caps_pressed + shift_pressed) % 2];
                    buffer[write_index++] = key;
                    write_index %= BUFFER_SIZE;
                    remaining_chars++;
                }
                break;
        }
    }
    int last = (write_index == 0) ? BUFFER_SIZE - 1 : write_index - 1;
    if(buffer[last] == 'r' && ctrl_pressed == 1){
        snapShotFlag = 1;
    }
}

char nextChar() {
    if(remaining_chars == 0) {
        return -1;
    }
    char c = buffer[read_index++];
    read_index %= BUFFER_SIZE;
    remaining_chars--;
    return c;
}

char * getBuffer() {
    return buffer;
}

char isCtrlPressed() {
    return ctrl_pressed;
}

// --- Funciones auxiliares ---

char isKeyPressed(int scancode) {
    if (scancode < 0 || scancode >= KEYS) {
        return 0;
    } 
    return getKeyPressed[scancode];
}

void setGameMode(int enabled) {
    inGameMode = enabled;
}