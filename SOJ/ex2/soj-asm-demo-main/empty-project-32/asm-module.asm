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
    extern g_x, g_y
    extern g_pole
    extern g_str
    extern g_c
    extern g_ic
    extern g_c2
    extern g_ic2
    extern g_c2_sum
    extern g_ic2_sum
    extern g_text
    extern g_cislo_i
    extern g_cislo_c
                                ;g_some_asm_var dd ?

;***************************************************************************

    section .text


    ;; CVICENI 4 ?

    global atoi__
atoi__:
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

    ;; CVICENI 3

    global suma_c_do_i2
suma_c_do_i2:
    enter 0,0
    ;; push edi
    mov edx, [ebp + 8]          ; *t_str
    mov eax, 0                  ; pocet_mezer = 0
.zpet
    cmp [edx], byte 0           ; while(*t_str != 0) {
    je .hotovo
    mov eax, [edx]
    inc edx
.taknic
    inc edx
    jmp .zpet                   ; }
.hotovo
    ;;  pop edi
    leave
    ret


    global suma_c_do_i
suma_c_do_i:
    enter 0,0
    push edi
    push esi

    mov ecx, [ebp + 12]         ; t_N
    mov edi, [ebp + 8]          ; *t_pole
    mov eax, 0                  ; suma
    mov edx, 0

.back
    movsx esi, byte [edi+edx]
    inc edx
    add eax, esi
    loop .back

    pop edi
    pop esi
    leave
    ret



    global soucet_lli_upravene
soucet_lli_upravene:
    enter 0,0

    mov eax, [ebp + 8]          ; a_low
    cdq
    adc eax, [ebp + 16]         ; += b_lo
    mov edx, [ebp + 12]         ; a_high

    leave
    ret

    global soucet_int_pole
soucet_int_pole:
    enter 0,0
    push edi

    mov ecx, [ebp + 12]         ; t_N
    mov edi, [ebp + 8]          ; *t_pole
    mov eax, 0                  ; suma
.back
    cdq
    add eax, [edi + ecx * 4 - 4]   ; suma += t_pole[ecx]

    loop .back

    pop edi
    leave
    ret

    global vatest
vatest:
enter 0,0
    push edi
    push esi
    mov edi, ebp
    add edi, 8
    mov eax, 0                  ; suma
    mov edx, 0

.back
    mov esi, [edi]
    cmp esi, -1
    je .hotovo
    add edi, 4
    add eax, esi
    loop .back

.hotovo
    pop edi
    pop esi
    leave
    ret



    global soucetll
soucetll:
    enter 0,0

    mov eax, [ebp + 8]          ; a_low
    add eax, [ebp + 16]         ; += b_low
    mov edx, [ebp + 12]         ; a_high
    adc edx, [ebp + 20]         ; b_high

    leave
    ret

    global imul_ii
imul_ii:
    enter 0,0

    mov eax, [ebp + 8]
    imul dword [ebp + 12]

    leave
    ret

    global idiv_lli
idiv_lli:
    enter 0,0

    mov eax, [ebp + 8]          ; a_low
    mov edx, [ebp + 12]         ; a_high
    idiv dword [ebp + 16]       ; /= b

    leave
    ret

    global idiv_ii
idiv_ii:
    enter 0,0

    mov eax, [ebp + 8]          ; a
    ;mov edx, 0 ; TAKTO NE -> NENI SIGNED ROZSIRENI
    cdq
    idiv dword [ebp + 12]


    leave
    ret


    ;; CVICENI 2

    global suma_pole
suma_pole:
    enter 0,0

    mov ecx, [ebp + 12]         ; t_N
    mov edx, [ebp + 8]          ; *t_pole
    mov eax, 0                  ; suma

.back
    add eax, [edx + (ecx - 1) * 4]
    ;add eax, [edx + ecx * 4 - 4]   ; suma += t_pole[ecx]
    loop .back

    leave
    ret



    global hledej_min
hledej_min:
    enter 0,0

    mov ecx, [ebp + 12]         ; t_N
    mov edx, [ebp + 8]          ; *t_pole
    ;mov eax, 0x7FFFFFFF
    mov eax, [edx + 0 * 4]              ; min = t_pole[0]

.back                           ; {
    cmp eax, [edx + ecx * 4 - 4] ; if (min > t_pole[ecx]) min = nove
    jle .taknic                  ; kdyby tady bylo jbe -> neznamenkove
    mov eax, [edx + ecx * 4 - 4]
.taknic
    loop .back                  ; }

    leave
    ret

    global pocet_mezer
pocet_mezer:
    enter 0,0
    ;; push edi
    mov edx, [ebp + 8]          ; *t_str
    mov eax, 0                  ; pocet_mezer = 0

.zpet
    cmp [edx], byte 0           ; while(*t_str != 0) {
    je .hotovo
    cmp [edx], byte ' '
    jne .taknic
    inc eax
.taknic
    inc edx
    jmp .zpet                   ; }
.hotovo
    ;;  pop edi
    leave
    ret

    ;; CVICENI 2

        global minmax
minmax:
    enter 0,0
    push edi
    ;; min -- [ebp + 16] -- max [ebp + 20]
    mov ecx, [ebp + 12]         ; t_N
    mov edx, [ebp + 8]          ; *t_pole
    mov eax, [edx + 0 * 4]      ; min = t_pole[0]
    mov edi, [edx + 0 * 4]      ; max = t_pole[0]

.back                           ; {
    cmp eax, [edx + ecx * 4 - 4] ; if (min > t_pole[ecx]) min = nove
    jle .taknic                  ; kdyby tady bylo jbe -> neznamenkove
    mov eax, [edx + ecx * 4 - 4]
.taknic
    cmp edi, [edx + ecx * 4 - 4]
    jnl .taknicc
    mov edi, [edx + ecx * 4 - 4]
.taknicc
    loop .back                  ; }

    mov edx, [ebp + 16]          ; *t_minmax
    mov [edx+4], edi
    mov [edx+0], eax
    pop edi
    leave
    ret

    global deleni
deleni:
    enter 0,0
    push edi
    push esi

    mov edi, [ebp + 16]
    mov ecx, [ebp + 12]
    mov edx, [ebp + 8]          ; *t_pole
    mov eax, 0                  ; suma

.back
    mov eax, [edx + ecx * 4 - 4]
    mov esi, ecx
    mov cl, [ebp + 16]
    sar eax, cl
    mov ecx, esi
    mov [edx + ecx * 4 - 4], eax
    loop .back

    pop edi
    pop esi
    leave
    ret

    global lichych
lichych:
    enter 0,0
    push edi
    mov edx, [ebp + 8]          ; *t_str
    mov eax, 0                  ; pocet_mezer = 0

.zpet
    cmp [edx],dword -1           ; while(*t_str != 0) {
    je .skoro
    mov edi, [edx]
    and edi, 1
    jz .taknic
    inc eax
.taknic
    add edx, 4                  ; todo
    jmp .zpet                   ; }
.skoro
    mov edi, [edx]
    and edi, 1
    jz .hotovo
    inc eax
.hotovo
    pop edi
    leave
    ret

    global bezkoncovych
bezkoncovych:
    enter 0,0
    ;; push edi
    mov edx, [ebp + 8]          ; *t_str
    mov eax, 0                  ; pocet_mezer = 0

.zpet
    cmp [edx], byte 0           ; while(*t_str != 0) {
    je .hotovo
    cmp [edx], byte ' '
    jne .taknic
    inc eax
.taknic
    inc edx
    jmp .zpet                   ; }
.hotovo
    ;;  pop edi
    leave
    ret

    ;; CVICENI 2 - KONEC

    global first_fun
first_fun:
    mov dword [g_x], 1234
    mov [g_y], dword 0x1234
    ret

    global init_pole
init_pole:
    mov dword [g_pole + 0 * 4], 2
    mov dword [g_pole + 1 * 4], 4
    mov dword [g_pole + 2 * 4], 8
    mov dword [g_pole + 3 * 4], 16
    ret

    global uprav_str
uprav_str:
    mov [g_str + 2], byte '!'
    ret

    global prohod
prohod:
    mov eax, [g_x]
    mov ecx, [g_y]
    mov [g_x], ecx
    mov [g_y], eax
    ret

    global c2ic
c2ic:
    movsx eax, byte [g_c]
    mov [g_ic], eax
    ret

    global jedna
jedna:
    movsx eax, byte [g_c2 + 0]
    mov [g_ic2 + 0 * 4], eax
    movsx eax, byte [g_c2 + 1]
    mov [g_ic2 + 1 * 4], eax
    movsx eax, byte [g_c2 + 2]
    mov [g_ic2 + 2 * 4], eax
    movsx eax, byte [g_c2 + 3]
    mov [g_ic2 + 3 * 4], eax
    ret

    global dva
dva:
    mov eax, [g_ic2 + 0 * 4]
    and eax, 0xfffffffe
    mov [g_ic2 + 0 * 4], eax

    mov eax, [g_ic2 + 1 * 4]
    and eax, 0xfffffffe
    mov [g_ic2 + 1 * 4], eax

    mov eax, [g_ic2 + 2 * 4]
    and eax, 0xfffffffe
    mov [g_ic2 + 2 * 4], eax

    mov eax, [g_ic2 + 3 * 4]
    and eax, 0xfffffffe
    mov [g_ic2 + 3 * 4], eax
    ret

    global tri
tri:
    ;; int arr
    mov eax, [g_ic2 + 0 * 4]
    add eax, [g_ic2 + 1 * 4]
    add eax, [g_ic2 + 2 * 4]
    add eax, [g_ic2 + 3 * 4]
    mov [g_ic2_sum], eax
    ;; char arr
    movsx ecx, byte [g_c2 + 0]
    mov eax, ecx
    movsx ecx, byte [g_c2 + 1]
    add eax, ecx
    movsx ecx, byte [g_c2 + 2]
    add eax, ecx
    movsx ecx, byte [g_c2 + 3]
    add eax, ecx
    mov [g_c2_sum], eax
    ret

    global ctyri
ctyri:
    mov ah, [g_text + 0]
    sub ah, 32
    mov [g_text + 0], ah
    mov ah, [g_text + 1]
    sub ah, 32
    mov [g_text + 1], ah
    mov ah, [g_text + 2]
    sub ah, 32
    mov [g_text + 2], ah
    mov ah, [g_text + 3]
    sub ah, 32
    mov [g_text + 3], ah
    ret

    global pet
pet:
    mov ah, [g_cislo_i + 0]
    mov [g_cislo_c + 3], ah
    mov ah, [g_cislo_i + 1]
    mov [g_cislo_c + 2], ah
    mov ah, [g_cislo_i + 2]
    mov [g_cislo_c + 1], ah
    mov ah, [g_cislo_i + 3]
    mov [g_cislo_c + 0], ah
    ret

    global sum
sum:
    enter 0,0
    mov eax, [ ebp + 8 ] ; parameter t_a
    add eax, [ ebp + 12 ] ; t_a += t_b
    leave
    ret


    global negative
negative:
    enter 0,0
	mov ecx, [ ebp + 12 ] ; length of t_array
	mov edx, [ ebp + 8 ] ; * t_array
	mov eax, 0 ; l_sum = 0
	.back :
	mov eax, [ edx + ecx * 4 - 4 ]; l_sum += t_array [ ecx -1]

    sub [edx + ecx * 4 - 4], eax
    sub [edx + ecx * 4 - 4], eax
    loop .back
	cdq ; extension of eax to edx
	leave
	ret

    global odd
odd:
    enter 0,0
	mov ecx, [ ebp + 12 ] ; length of t_array
	mov edx, [ ebp + 8 ] ; * t_array
	mov eax, 0 ; l_sum = 0
	.back :
	mov eax, [ edx + ecx * 4 - 4 ]; l_sum += t_array [ ecx -1]
    or eax, 0x0001
    mov[ edx + ecx * 4 - 4 ], eax
    loop .back
	cdq ; extension of eax to edx
	leave
	ret

    global num_of_even
num_of_even:
	enter 0,0
	mov ecx, [ ebp + 12 ] ; length of t_array
	mov edx, [ ebp + 8 ] ; * t_array
	mov eax, 0 ; l_sum = 0
    mov edi, 0
    .back :
	mov edi, [ edx + ecx * 4 - 4 ]
    or edi, 0x0001
    sub edi, [ edx + ecx * 4 - 4 ]
    mov [ edx + ecx * 4 - 4 ], edi
    add eax, [ edx + ecx * 4 - 4 ]
    loop .back
    leave
	ret

    global test
test:
    enter 0,0
    mov ecx, [ebp + 8]
    mov eax, ecx
    leave
    ret

    global decode
decode:
enter 0,0
	mov ecx, [ ebp + 12 ] ; length of t_array
	mov edx, [ ebp + 8 ] ; * t_array
	mov eax, 0
    .back :
	mov ax, [ edx + ecx * 2 - 2 ]
    xor ax, 0xffff
    mov [ edx + ecx * 2 - 2 ], ax
    loop .back
    leave
	ret


    ; functions

    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret
