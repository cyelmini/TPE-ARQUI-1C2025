GLOBAL cpuVendor
GLOBAL getKey
GLOBAL getHours
GLOBAL getMinutes
GLOBAL getSeconds
GLOBAL stopSound
GLOBAL makeSound

section .text

cpuVendor:
    push rbp
    mov rbp, rsp

    push rbx

    mov rax, 0
    cpuid

    mov [rdi], ebx
    mov [rdi + 4], edx
    mov [rdi + 8], ecx

    mov byte [rdi+13], 0

    mov rax, rdi

    pop rbx

    mov rsp, rbp
    pop rbp
    ret

getHours:
    cli
    mov al, 04h
    out 70h, al
    in al, 71h
    sti
    ret

getMinutes:
    cli
    mov al, 02h
    out 70h, al
    in al, 0x71
    sti
    ret

getSeconds:
    cli
    mov al, 00h
    out 70h, al
    in al, 71h
    sti
    ret

getKey:
    in al, 64h
    test al, 1
    jz .no_key

    in al, 60h
    movzx rax, al
    ret
.no_key:
    xor rax, rax
    ret

makeSound:
    push rbp
    push rdx
    mov rbp, rsp

    mov al, 0xB6
    out 43h, al

    xor rdx, rdx
    mov rax, 1193180
    div rdi

    out 42h, al
    mov al, ah
    out 42h, al

    in al, 61h
    or al, 03h
    out 61h, al

    mov rsp, rbp
    pop rdx
    pop rbp
    ret

stopSound:
    in al, 61h
    and al, 0xFC
    out 61h, al
    ret