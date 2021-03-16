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

    ; Save argc, argv, and envp
    push rdi
    push rsi
    push rdx

    call initializeStandardLibrary
    
    call _init

    pop rdx
    pop rsi
    pop rdi
    call main

    mov rdi, rax
    call exit