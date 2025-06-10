GLOBAL divisionByZero
GLOBAL invalidOpCode

section .text

divisionByZero: 
mov rax, 0
div rax 
ret

invalidOpCode:
ud2 
ret