;***************************************************************************
;
; Program for education in subject "Assembly Languages" and "APPS"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************

    bits 64

    section .data

    ; variables

    ;global g_some_asm_var
    ;extern g_some_c_var

;g_some_asm_var dd ?

;***************************************************************************

    section .text

    ; functions

    ;global some_asm_function
    ;extern some_c_function


    ; RDI, RSI, RDX, RCX, R8 a R9
    ; EDI, ESI, EDX, ECX, R8D, R9D

    global num0
num0:
    enter 0,0
    mov cl, -1                   ; <0 - 63>
    mov r8, 64
    mov rdx, -1
    mov esi, 0

.back
    inc rdx

    cmp rdx, r8
    jge .done

    mov cl, dl

    mov rax, rdi
    shr rax, cl

    and rax, 0x0000000000000001

    cmp rax, 0
    jne .back

    inc esi
    loop .back

.done
    mov eax, esi
    leave
    ret

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    global num1
num1:
    enter 0,0
    mov cl, -1                   ; <0 - 63>
    ;mov r8, 64
    mov rdx, -1
    mov esi, 0

.back
    inc rdx

    cmp rdx, 64
    jge .done

    mov cl, dl

    mov rax, rdi
    shr rax, cl

    and rax, 0x0000000000000001

    cmp rax, 1
    jne .back

    inc esi
    loop .back

.done
    mov eax, esi
    leave
    ret

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    ; RDI, RSI, RDX, RCX, R8 a R9
    ; EDI, ESI, EDX, ECX, R8D, R9D


    global nejvetsi
nejvetsi:
    enter 0,0
    mov r8, -1
    mov r9, rdi

.back
    inc r8

    cmp r8, rsi
    je .done

    ; alg
    mov rax, [r9 + r8 * 8]

    ; call function
    mov rdi, rax
    call num1

    loop .back

.done
    ;mov eax, [rdi + 0 * 8]
    leave
    ret

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    global test
test:
    enter 0,0
    mov r9, rdi                  ; l_array
    mov r8, -1                   ; index
    mov r10, 0                   ; tmp for comparing
    mov r11, 0                   ; final index

.back
    inc r8

    cmp r8, rsi
    jge .done

    mov rdi, [r9 + r8 * 8]
    call num1
    mov r10, rax

    mov rdi, [r9 + r11 * 8]     ; current_max
    call num1

    cmp r10, rax
    jge .prepis

    loop .back

.prepis
    mov r11, r8
    loop .back

.done

    mov rax, r11
    ; clear
    mov r10, 0
    mov r11, 0
    leave
    ret

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; RDI, RSI, RDX, RCX, R8 a R9
    ; EDI, ESI, EDX, ECX, R8D, R9D


    global str2long
str2long:
    enter 0,0
    xor rax, rax
    xor rdx, rdx
    xor r10, r10
    xor r11, r11


    mov r8, 0                   ; len
    mov r9, 0                   ; result
    mov rdx, 1                  ; mocnina pro nasobeni
    mov r11, 1
    mov r10, 10                 ; for multiplication
    mov rax, 0

.back1
    mov dl, [rdi + r8]
    cmp dl, 0
    je .done1

    inc r8
    loop .back1

    cbw
    cwd
    cdq
    cqo

.done1
    ; go back to 0
    dec r8

    cmp r8, 0                   ; sign at 0 -> last step
    je .done2

    ; alg
    mov dl, [rdi + r8]
    sub dl, 48
    movzx r10, dl


    imul r10, r11
    add rax, r10

    imul r11, 10

    loop .done1

.done2
    ; take care of sign
    mov dl, [rdi + 0]
    cmp dl, '+'
    je .done3

    jmp .done4

.done3
    ;mov rax, r10

    xor r10, r10
    xor r11, r11

    leave
    ret

.done4
    ;mov rax, r10
    imul rax, -1
    ;neg rax

    xor r10, r10
    xor r11, r11

    leave
    ret


;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; RDI, RSI, RDX, RCX, R8 a R9
    ; EDI, ESI, EDX, ECX, R8D, R9D



;some_asm_function:
    ;ret
