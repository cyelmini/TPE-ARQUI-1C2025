GLOBAL syscall_read
GLOBAL syscall_write
GLOBAL syscall_seconds
GLOBAL syscall_minutes
GLOBAL syscall_hours
GLOBAL syscall_sound
GLOBAL syscall_setCursor
GLOBAL syscall_getCursorX
GLOBAL syscall_getCursorY
GLOBAL syscall_getScreenHeight
GLOBAL syscall_clearScreen

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

syscall_getScreenHeight:
    mov rax, 0x09
    int 0x80
    ret

syscall_getRegisters:
    mov rax, 0x0A
    int 0x80
    ret

syscall_clearScreen:
    mov rax,0x0B
    int 0x80
    ret