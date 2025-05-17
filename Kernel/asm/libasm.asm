GLOBAL cpuVendor
GLOBAL getKey

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


;getHours:
				; use instruction "cli" to disable interruptions 
;	push rbp
;	mov rbp, rsp ; stack frame
;	mov al, 0x04 ; selects hour system registry from RTC
;	out 70h, al  ; sends the value to the adress of RTC
;	in al, 71h	 ; reads the value where RTC stores the answer

;	mov rsp, rbp
;	pop rbp
				; use instruction "sti" to enable interruptions 
;	ret


;getMinutes:
;	push rbp
;	mov rbp, rsp
;	mov al, 0x02
;	out 70h, al
;	in al, 0x71
;
;	mov rsp, rbp
;	pop rbp
;	ret


;getSeconds:


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
