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

    global add_intN_intN
add_intN_intN:
	%define par_cislo1 rdi
	%define par_cislo2 rsi
	%define par_N rdx

	mov rcx, par_N
	clc						; vynulovani carry flagu, CF = 0
	mov rdx, 0

.smycka:
	mov eax, [rsi + rdx * 4]	; eax = rsi[index]
	adc [rdi + rdx * 4], eax	; rdi[index] += eax
	inc rdx						; index++
	loop .smycka

	mov rax, 0
	adc rax, 0		; setc al, nastaveni carry flagu

	ret


    global sub_intN_intN
sub_intN_intN:
	%define par_cislo1 rdi
	%define par_cislo2 rsi
	%define par_N rdx

	mov rcx, par_N
	clc						; vynulovani carry flagu, CF = 0
	mov rdx, 0

.smycka:
	mov eax, [rsi + rdx * 4]	; eax = rsi[index]
	sbb [rdi + rdx * 4], eax	; rdi[index] -=  eax
	inc rdx						; index++
	loop .smycka

	mov rax, 0
	adc rax, 0		; setc al, nastaveni carry flagu

	ret

    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret
