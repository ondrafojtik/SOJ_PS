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

    global add_intN_int32
add_intN_int32:
    %define par_cislo rdi
	%define par_scitatel esi
	%define par_N edx

	movsx rcx, par_N			; ecx = N
	dec rcx						; prvni cislo nasobime rovnou
	mov rdx, 1

	add [par_cislo], par_scitatel	; n[0] += scitanec

.back:
	jnc .konec
	adc [par_cislo + rdx * 4], DWORD 0
	inc rdx

	loop .back

.konec:
	ret


    global mul_intNint32
mul_intNint32:
    %define par_cislo rdi
	%define par_nasobitel esi
	%define par_pocet edx

	movsx rcx, par_pocet
	mov r8, 0					; mezivysledek

.back:
	movsx rax, DWORD [par_cislo]; eax = *cislo
	mul DWORD par_nasobitel		; eax *= nasobitel

	add rax, r8					; secteni s predchozim mezivysledkem
	adc rdx, 0					; pridani pripadneho preteceni
	mov r8, rdx					; ulozeni mezivysledku pro dalsi kolo

	mov [par_cislo], eax		; *cislo = eax
	;add par_cislo, 4			; cislo++

	loop .back

	ret



    global div_intN_int32
div_intN_int32:
	%define par_cislo rdi
	%define par_delitel esi
	%define par_N edx

	movsx rcx, par_N				; velikost cisla
	mov rdx, 0						; zbytek

.back:
	movsx rax, DWORD [par_cislo + rcx * 4 - 4]	; eax = n[ecx - 1]
	div DWORD par_delitel						; vydeleni
	mov [par_cislo + rcx * 4 - 4], eax			; n[ecx - 1] = eax

	loop .back

	mov rax, rdx					; navratova hodnota - zbytek

	ret


    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret
