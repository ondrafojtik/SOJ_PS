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
    ; rdi, rsi, rdx, rcx, r8, r9, xmm0..xmm7


    global jedna
jedna:
    mov eax, 15
    cvtsi2ss xmm2, eax          ; xmm2 = 15 (n)

    mov eax, 1
    cvtsi2ss xmm3, eax          ; xmm3 = 1
    cvtsi2ss xmm4, eax          ; vysledek

.back
    subss xmm2, xmm3
    movss xmm0, xmm2
    call factorial
    movss xmm6, xmm3
    divss xmm6, xmm0            ; 1 / fact
    addss xmm4, xmm6            ; e += ..
    comiss xmm2, xmm3
    je .done


    loop .back
.done
    movss xmm0, xmm4
    ret

    global factorial
factorial:
    movss xmm1, xmm0
    mov eax, 1
    cvtsi2ss xmm2, eax
.back
    subss xmm1, xmm2
    mulss xmm0, xmm1
    comiss xmm1, xmm2
    je .done
    loop .back
.done
    ret

    global ctyri
ctyri:
    mov eax, 0                  ; counter
    movsx rcx, esi
    movss xmm0, dword [rdi + rcx * 4 - 4]     ; min = array[0]
    movss xmm1, dword [rdi + rcx * 4 - 0]
    movss xmm2, dword [rdi + rcx * 4 + 4]
.back
    ; loading
    movss xmm0, dword [rdi + rcx * 4 - 4]     ; min = array[0]
    movss xmm1, dword [rdi + rcx * 4 - 0]
    movss xmm2, dword [rdi + rcx * 4 + 4]
    ; calculation
    mulss xmm0, xmm0
    mulss xmm1, xmm1
    mulss xmm2, xmm2
    addss xmm0, xmm1
    comiss xmm0, xmm2
    ja .skip
    comiss xmm0, xmm2
    jb .skip
    inc eax
.skip
    loop .back

    cvtsi2ss xmm3, eax
    movss xmm0, xmm3
    ret


    global povrch_koule
povrch_koule:
    movss xmm4, xmm0
    mulss xmm4, xmm4
    mov eax, 4
    cvtsi2ss xmm0, eax
    mulss xmm0, xmm1
    mulss xmm0, xmm4
    ret

    global objem_koule
objem_koule:
    movss xmm4, xmm0
    movss xmm5, xmm0
    mulss xmm4, xmm5
    mulss xmm4, xmm5
    mulss xmm4, xmm1

    mov eax, 4
    cvtsi2ss xmm0, eax
    mov eax, 3
    cvtsi2ss xmm3, eax
    divss xmm0, xmm3
    mulss xmm0, xmm4
    ret


    global uhlopricka
uhlopricka:
    mulss xmm0, xmm0
    mulss xmm1, xmm1
    addss xmm0, xmm1
    sqrtss xmm0, xmm0
    ret

    global abs_d
abs_d:
    movsd xmm1, xmm0
    mov eax, -1
    cvtsi2sd xmm2, eax          ; xmm2 = -1
    mulsd xmm1, xmm2            ; xmm1 *= xmm2
    maxsd xmm0, xmm1            ; max()
    ret

    global in_range
in_range:
    movsx rcx, esi
    mov eax, 0                  ; counter (return value)

.back
    comiss xmm0, [rdi + rcx * 4 - 4]
    ja .skip
    comiss xmm1, [rdi + rcx * 4 - 4]
    jb .skip
    inc eax
.skip
    loop .back

    ret

    global min_f
min_f:
    movsx rcx, esi
    movss xmm0, dword [rdi]     ; min = array[0]

.back
    minss xmm0, [rdi + rcx * 4 - 4]
    loop .back

    ret


    global prumer_f
prumer_f:
    call suma_f                 ; xmm0 = soucet suma_f
    cvtsi2ss xmm1, esi          ; esi = t_N (nemuzeme delit intem..)
    divss xmm0, xmm1
    ret

    global suma_f
suma_f:
    movsx rcx, esi
    xorps xmm0, xmm0    ; xmm0 = 0
.back
    addss xmm0, [rdi + rcx * 4 - 4]
    loop .back

    ret

    global add_d
add_d:
    addsd xmm0, xmm1
    ret

    global f2f, d2d
f2f:
d2d:
    ret


    global f2d
f2d:
    cvtss2sd xmm0, xmm0
    ret

    global d2f
d2f:
    cvtsd2ss xmm0, xmm0
    ret



;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    global add_intNint32
add_intNint32:
    ;rdi += esi (edx == base)

	movsx rcx, edx			; ecx = N + sign extend
	dec rcx                 ; skip t_a[0]
	mov rdx, 0
	add [rdi], esi	        ; t_a [ 0 ] += t_b

.back:
    inc rdx
	jnc .done               ; jump if not carry
	adc [rdi + rdx * 4], dword 0

	loop .back

.done:
	ret


    global mul_intNint32
mul_intNint32:
    ; rdi *= esi (edx == base)

    movsx rcx, edx
	mov r8, 0					; mov edi, 0 || carry

.back:
	movsx rax, dword [rdi]
	mul dword esi
	add rax, r8
	adc rdx, 0
	mov r8, rdx
	mov [rdi], eax
	add rdi, 4

    loop .back

	ret

    global div_intNint32
div_intNint32:
    ; rdi /= esi (edx == base)
    movsx rcx, edx
	mov rdx, 0			                    ; remainder = 0

.back:
	movsx rax, dword [rdi + rcx * 4 - 4]	; eax = t_a [ ecx - 1 ]
	div dword esi
	mov [rdi + rcx * 4 - 4], eax			; t_a [ ecx - 1 ] = eax

	loop .back

	mov rax, rdx                            ; eax = remainder
    ret

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    global add_intNintN
add_intNintN:
	mov rcx, rdx
	mov rdx, 0
    clc

.back:
	mov eax, [rsi + rdx * 4]
	adc [rdi + rdx * 4], eax	;  t_a [ inx ]+= t_b [ inx ]+ cf
	inc rdx
	loop .back

	ret


    global sub_intNintN
sub_intNintN:
	mov rcx, rdx
	mov rdx, 0
    clc

.back:
	mov eax, [rsi + rdx * 4]
	sbb [rdi + rdx * 4], eax    ; jediny rozdil oproti add
	inc rdx
	loop .back

	ret

    global shl_intN
shl_intN:
	mov rcx, rsi
	mov rdx, rdi
	mov rax, 0
	clc

.back:
	rcl dword [rdx + rax * 4], 1
	inc rax
	loop .back

	ret

    global shr_intN
shr_intN:
	mov rcx, rsi
	mov rdx, rdi
	mov rax, 0
	clc

.back:
	rcr dword [rdx + rax * 4], 1
	inc rax
	loop .back

	ret



    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret
