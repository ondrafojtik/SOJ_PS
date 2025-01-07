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

    ;global some_asm_function
    ;extern some_c_function


    global soucet
soucet:
    enter 0,0
    push esi
    push edi

    mov ecx, 0                 ; index

    mov edi, [ebp + 8]          ; jedna
    mov esi, [ebp + 12]         ; dva
    mov edx, [ebp + 16]         ; vysledek

.back

    mov eax, [edi + 4 * ecx]
    add eax, [esi + 4 * ecx]
    mov [edx + 4 * ecx], eax

    inc ecx

    cmp ecx, [ebp + 20]
    je .done

    jmp .back

.done
    mov eax, ecx
    pop esi
    pop edi
    leave
    ret

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;some_asm_function:
    ;ret
