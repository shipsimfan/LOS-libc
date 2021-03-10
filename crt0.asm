GLOBAL _start
EXTERN main
EXTERN initializeStandardLibrary
EXTERN exit
EXTERN _init
_start:
    ; Setup end of stack frame
    xor rbp, rbp
    push rbp
    push rbp
    mov rbp, rsp

    call initializeStandardLibrary
    
    call _init

    call main

    mov rdi, rax
    call exit