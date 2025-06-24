GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _sysCallsHandler
GLOBAL saveRegs

GLOBAL registers

GLOBAL _exception0Handler
GLOBAL _exception01Handler
GLOBAL printRegs

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sysCallDispatcher
EXTERN printf
EXTERN printRegisters
EXTERN getStackBase
ExTERN retUserland

SECTION .data
print_fmt_regs: db "rax=%d rbx=%d rcx=%d rdx=%d rsi=%d rdi=%d", 10, 0

SECTION .text

%macro pushState 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro popState 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

%macro irqHandlerMaster 1
    pushState

    mov rdi, %1
    jne .next

    saveRegs

.next:
    mov rsi, rsp
    mov rdi, %1
    call irqDispatcher

    mov al, 20h
    out 20h, al

    popState
    iretq
%endmacro

%macro saveRegs 0
    mov [registers+8*0],    rax
    mov [registers+8*1],    rbx
    mov [registers+8*2],    rcx
    mov [registers+8*3],    rdx
    mov [registers+8*4],    rsi
    mov [registers+8*5],    rdi
    mov [registers+8*6],    rbp
    mov [registers+8*7],    r8
    mov [registers+8*8],    r9
    mov [registers+8*9],    r10
    mov [registers+8*10],   r11
    mov [registers+8*11],   r12
    mov [registers+8*12],   r13
    mov [registers+8*13],   r14
    mov [registers+8*14],   r15

    
    mov rax, [rsp+8*15]      ; RIP
    mov [registers+8*15], rax
    mov rax, [rsp+8*16]      ; CS
    mov [registers+8*16], rax
    mov rax, [rsp+8*17]      ; RFLAGS
    mov [registers+8*17], rax
    mov rax, [rsp+8*18]      ; RSP
    mov [registers+8*18], rax
%endmacro

%macro exceptionHandler 1
    pushState
    saveRegs

    mov rdi, %1
    call exceptionDispatcher

    popState
    call getStackBase
    sub rax, 20h
    mov qword [rsp+8*3], rax
    call retUserland
    mov qword [rsp], rax
    iretq
%endmacro

printRegs:
    mov qword rdi, registers
    call printRegisters
    ret

%macro sysCallsHandlerMaster 0
    pushState
    mov rbp, rsp

    push r9
    mov r9, r8
    mov r8, rcx
    mov rcx, rdx
    mov rdx, rsi
    mov rsi, rdi
    mov rdi, rax
    call sysCallDispatcher
    mov [aux], rax

    mov al, 20h
    out 20h, al

    pop r9
    mov rsp, rbp
    popState

    mov rax, [aux]
    iretq
%endmacro

_hlt:
    sti
    hlt
    ret

_cli:
    cli
    ret

_sti:
    sti
    ret

picMasterMask:
    push rbp
    mov rbp, rsp
    mov ax, di
    out 21h, al
    pop rbp
    retn

picSlaveMask:
    push rbp
    mov rbp, rsp
    mov ax, di
    out 0A1h, al
    pop rbp
    retn

;8254 Timer (Timer Tick)
_irq00Handler:
    irqHandlerMaster 0

;Keyboard
_irq01Handler:
    irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
    irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
    irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
    irqHandlerMaster 4

;USB
_irq05Handler:
    irqHandlerMaster 5

;Zero Division Exception
_exception0Handler:
    exceptionHandler 0

;Invalid Code Exception
_exception01Handler:
    exceptionHandler 6

;SysCalls Interruptions Handler
_sysCallsHandler:
    sysCallsHandlerMaster

haltcpu:
    cli
    hlt
    ret

SECTION .bss
    aux resq 1
    registers resq 19