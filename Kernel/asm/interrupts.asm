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

GLOBAL _exception0Handler

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sysCallDispatcher		

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

	mov rdi, %1 	; interruption number(1 = keyboard)
	cmp rdi, 1
	jne .next

	saveRegs

	.next:
	mov rsi, rsp
	mov rdi, %1
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro saveRegs 0
	mov [registers+8*0], 	rax
	mov [registers+8*1],	rbx
	mov [registers+8*2],	rcx
	mov [registers+8*3],	rdx
	mov [registers+8*4],	rsi
	mov [registers+8*5],	rdi
	mov [registers+8*6],	rbp
	mov [registers+8*7], 	r8
	mov [registers+8*8], 	r9
	mov [registers+8*9], 	r10
	mov [registers+8*10], 	r11
	mov [registers+8*11], 	r12
	mov [registers+8*12], 	r13
	mov [registers+8*13], 	r14
	mov [registers+8*14], 	r15

	mov rax, rsp

	add rax, 160  

	mov [registers+8*15], 	rax 
	mov rax, [rsp+15*8] 
	mov [registers+8*16], 	rax 
	mov rax, [rsp+17*8]
	mov [registers+8*17], 	rax

%endmacro

%macro exceptionHandler 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState
	iretq
%endmacro

; cuando se hace una int80h (interrupcion de software), la interruption table lo manda a la funcion sysCallsHandler (en este archivo), la cual ejecuta 
; esta macro. La misma setea en los registros requeridos los parametros de la syscall para llamar a la funcion en C "sysCallDispatcher", la cual decide, 
; segun lo que hay en rdi, qué syscall ejecutar. Los parámetros se pasan asi en lugar de en orden (primero a ultimo) porque para pasar los parametros 
; se pisa donde hay otros parametros, y este es el unico orden donde no se pisan :3

%macro sysCallsHandlerMaster 0
	pushState

	; organizo los parametros para llamar a una funcion segun la convecion de llamado de funcion a C
	mov rcx, rdx  
	mov rdx, rsi   
	mov rsi, rdi  
	mov rdi, rax   
	push r8
	mov r8, r10		; 6 param tabla syscall
	mov r10, r9 	; 5 param tabla syscall 
	pop r8
	mov r9, r8		; 7 param tabla syscall

	call sysCallDispatcher

	mov al, 20h 	; avisa al pic que termino la interrupcion 
	out 20h, al

	popState
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
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
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

;SysCalls Interruptions Handler
_sysCallsHandler:
	sysCallsHandlerMaster

haltcpu:
	cli
	hlt
	ret

SECTION .bss
	aux resq 1
	registers resq 18