GLOBAL sys_read
GLOBAL sys_write
GLOBAL sys_seconds
GLOBAL sys_minutes
GLOBAL sys_hours
GLOBAL sys_sound

section.text

sys_call_read:
    mov rax, 0x00
    int 80h
    ret

sys_call_write:
    mov rax, 0x01
    int 80h
    ret