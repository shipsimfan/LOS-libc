GLOBAL _start
EXTERN main
EXTERN initializeStandardLibrary
_start:
    call initializeStandardLibrary
    
    call main

    mov rsi, rax
    xor rdi, rdi
    syscall