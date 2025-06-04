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
	cli				; use instruction "cli" to disable interruptions 

	mov al, 04h 	; selects hour system registry from RTC
	out 70h, al  	; sends the value to the adress of RTC
	in al, 71h	 	; reads the value where RTC stores the answer

	sti				; use instruction "sti" to enable interruptions 
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

	mov al, 0xB6 		; loads the command to configure channel 2 of the PIT in order to generate sound
	out 43h, al 		; sends the command to port 43h which is the control port of the PIT;

	xor rdx, rdx 		; cleans rdx
	mov rax, 1193180 	; loads the base frecuency of the PIT
	div rdi				; rdi contains the desired sound, results is stored in rax

	out 42h, al 		; sends the lower byte of rax to port 42h (channel 2 of the PIT)
	mov al, ah 			; moves the higher byte of rax
	out 42h, al 		; sends the higher byte to the port 42h

	in al, 61h			; reads port 61h which is the registry where the system speaker is 
	or al, 03h 			; activates the PIT and the speaker 
	out 61h, al 		; sends the value back to 61h

	mov rsp, rbp
	pop rdx
	pop rbp
	ret

stopSound:
	in al, 61h			;reads port 61h which is the registry where the system speaker is 
	and al, 0xFC		; puts in 0 both channel 2 of the PIT and the speaker to turn off sound
	out 61h, al 
	ret