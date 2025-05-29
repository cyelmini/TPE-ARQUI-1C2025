GLOBAL syscall_read
GLOBAL syscall_write
GLOBAL syscall_seconds
GLOBAL syscall_minutes
GLOBAL syscall_hours
GLOBAL syscall_sound
GLOBAL syscall_setCursorX
GLOBAL syscall_setCursorY
GLOBAL syscall_cursorX
GLOBAL syscall_cursorY

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
    mov rax, 0x03
    int 80h
    ret

syscall_minutes:
    mov rax, 0x04
    int 80h
    ret

syscall_hours:
    mov rax, 0x05
    int 80h
    ret

syscall_sound:
    mov rax, 0x06
    int 80h
    ret

syscall_setCursorX:
    mov rax, 0x07
    int 80h
    ret

syscall_setCursorY:
    mov rax, 0x08
    int 80h
    ret

syscall_cursorX:
    mov rax, 0x09
    int 80h
    ret

syscall_cursorY:
    mov rax, 0x0A
    int 80h
    ret

