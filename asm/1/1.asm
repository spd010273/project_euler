section .bss
    outbuff resb 4
section .data
    errmsg db 'Error', 0xa
    errlen equ $ - errmsg
section .text

global _start

_start:
    mov esi, 1000 ; itr -> 0
    sub edi, edi  ; edi = running sum

    _loop:
        cmp esi, 0
        je _finished ; exit loop if we went 1000 times
        sub edx, edx
        mov eax, esi
        mov ebx, 5
        idiv ebx
        cmp edx, 0
        je _plus
        sub edx, edx
        mov ebx, 3
        idiv ebx
        cmp edx, 0
        je _plus
        sub edx, edx
        dec esi
        jmp _loop
    _plus:
        add edi, esi
        dec esi
        jmp _loop
    _finished:
        jmp _print

    _print: ; print integer stored in edi encoded as ASCII
        ; need to find length, store in esi
        mov esi, 32
        mov eax, edi
        _numlen:
            dec esi
            shr eax, 1
            cmp eax, 0
            jnz _numlen
            cmp esi, 0
            jle _error
        _printloop:
            mov eax, 4
            mov ebx, 1
            shr edi, 1
            mov ecx, edi
            add ecx, 0x30
            dec esi
            mov edx, 1
            int 0x80
            cmp esi, 0
            je _exit
            jmp _printloop
_exit:
    mov eax, 1
    int 0x80
_error:
    mov edx, errlen
    mov ecx, errmsg
    mov ebx, 1
    mov eax, 4
    int 0x80
    jmp _exit
