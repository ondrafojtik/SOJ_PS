;***************************************************************************
;
; Program for education in subject "Assembly Languages" and "APPS"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************

    bits 32

    section .data

    ; variables

    ;global g_some_asm_var
    ;extern g_some_c_var

;g_some_asm_var dd ?

;***************************************************************************

    section .text

    ; functions

    global jedna
jedna:
    enter 0, 0
	push edi
	mov edi, [ebp + 8]
	mov esi, edi
	mov ecx, 0
.back:
	lodsb
	cmp al, 0
	jz .done

	mov dl, al
	add dl, 32

	cmp al, 'a'
	cmovae edx, eax
	mov al, dl

	stosb
	jmp .back
.done:
	pop edi
	leave
	ret

    global dva
dva:
    enter 0,0
    push edi
    push esi

    ; 7
    mov edi, eax
    mov esi, 00000001b
    and edi, esi
    shr edi, 0
    mov eax, edi
    mov ecx, eax

    ; 0
    mov edi, eax
    mov esi, 10000000b
    and edi, esi
    shr edi, 7
    mov eax, edi

    pop edi
    pop esi
    leave
    ret

    global tri
tri:
    enter 0, 0
	push edi
	mov edi, [ebp + 8]
	mov esi, edi
	mov ecx, 0
.back:
	lodsb
	cmp al, 0
	jz .done

    cmp al, ' '
    je .back

	cmp al, ' '
	cmovne edx, eax

    inc ecx
    mov al, dl
    ;inc ecx

	stosb
	jmp .back

.done:
    ; remove last characters
    mov eax, 0
    mov edi, [ebp + 8]
    mov esi, edi
.back1
    cmp eax, ecx
    je .done1
    inc eax

    jmp .back1
.done1
    mov byte [edi + ecx], 0
    ;mov eax, ecx
	pop edi
	leave
	ret


    global ctyri
ctyri:
    enter 0,0
    push edi
    push esi

    mov ecx, [ebp + 20]           ; t_N
    mov edi, [ebp + 8]            ; *jedna
    mov esi, [ebp + 12]          ; *dva
    mov edx, [ebp + 16]          ; *tri

.back
    mov eax, [edi + ecx * 4 - 4]
    add eax, [esi + ecx * 4 - 4]
    mov [edx + ecx * 4 - 4], eax
    loop .back
.done
    pop edi
    pop esi
    leave
    ret



    global pet
pet:
	enter 0, 0
    push edi
    push ebx
    mov ebx, [ebp + 8]
    mov eax, 0
    mov edx, 0
	mov ecx, ebx
	inc ecx

    ;; negative handle
	cmp [ebx], BYTE '-'
	cmove ebx, ecx

	mov ecx, 0

.charhandle:
	cmp [ebx + ecx], BYTE 0
	je .hotovo

    ;; only numbers..
	cmp [ebx + ecx], BYTE '0'
	jl .hotovo
	cmp [ebx + ecx], BYTE '9'
	jg .hotovo

    ;; algorithm
    ;movsx dword edi, byte [ebx + ecx]
    ;sub edi, '0'
    ;;
    ;cdq
    ;imul eax, 10
    ;add eax, edi
    ;adc edx, 0

    cdq
    ;imul eax, 10
    ;mov edi, [ebx + ecx]
	;add eax, edi         ; char..
    ;sub eax, '0'
    ;adc edx, 0

    cdq
    movzx edi, byte [ebx + ecx]
    sub edi, '0'

    imul eax, 10
    add eax, edi
    adc edx, 0

    ;; i++
	inc ecx
	jmp .charhandle

.hotovo:
    ;; negative handle
	mov ebx, [ebp + 8]
	mov ecx, eax
	imul eax, -1
	cmp [ebx], BYTE '-'
	cmovne eax, ecx


	pop ebx
    pop edi
    leave
	ret


    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret
