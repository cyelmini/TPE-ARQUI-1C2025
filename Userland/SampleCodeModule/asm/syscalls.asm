GLOBAL syscall_read
GLOBAL syscall_write
GLOBAL syscall_seconds
GLOBAL syscall_minutes
GLOBAL syscall_hours
GLOBAL syscall_sound
GLOBAL syscall_setCursor
GLOBAL syscall_getCursorX
GLOBAL syscall_getCursorY
GLOBAL syscall_drawCursor
GLOBAL syscall_getScreenHeight
GLOBAL syscall_getScreenWidth
GLOBAL syscall_getRegisters
GLOBAL syscall_clearScreen
GLOBAL syscall_changeCharSize
GLOBAL syscall_defaultCharSize
GLOBAL syscall_changeBackgroundColor
GLOBAL syscall_colorWrite
GLOBAL syscall_putRectangle
GLOBAL syscall_drawCircle

section .text

syscall_read:
    mov rax, 0x00
    int 0x80
    ret

syscall_write:
    mov rax, 0x01
    int 0x80
    ret

syscall_seconds:
    mov rax, 0x02
    int 0x80
    ret

syscall_minutes:
    mov rax, 0x03
    int 0x80
    ret

syscall_hours:
    mov rax, 0x04
    int 0x80
    ret

syscall_sound:
    mov rax, 0x05
    int 0x80
    ret

syscall_setCursor:
    mov rax, 0x06
    int 0x80
    ret

syscall_getCursorX:
    mov rax, 0x07
    int 0x80
    ret

syscall_getCursorY:
    mov rax, 0x08
    int 0x80
    ret

syscall_drawCursor:
    mov rax, 0x09
    int 0x80
    ret

syscall_getScreenHeight:
    mov rax, 0x0A
    int 0x80
    ret

syscall_gretScreenWidth:
    mov rax, 0x0B
    int 0x80
    ret

syscall_getRegisters:
    mov rax, 0x0C
    int 0x80
    ret

syscall_clearScreen:
    mov rax,0x0D
    int 0x80
    ret

syscall_changeCharSize:
    mov rax, 0x0E
    int 0x80
    ret

syscall_defaultCharSize:
    mov rax, 0x0F
    int 0x80
    ret

syscall_changeBackgroundColor:
    mov rax, 0x10
    int 0x80
    ret

syscall_colorWrite:
    mov rax, 0x11
    int 0x80
    ret

syscall_putRectangle:
    mov rax, 0x12
    int 0x80
    ret

syscall_drawCircle:
    mov rax, 0x13
    int 0x80
    ret