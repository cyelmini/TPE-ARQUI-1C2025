GLOBAL divisionByZero
GLOBAL invalidOpCode

section .text

divisionByZero: 
mov rax, 0
div rax ; the invalid division is forced
ret

invalidOpCode:
ud2 ; the invalid operation is forced
ret