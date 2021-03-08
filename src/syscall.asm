GLOBAL SystemCall
SystemCall:
    push r10
    mov r10, rcx
    syscall
    pop r10
    
    ret