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

    ; ex 1

    extern g_int_x
    extern g_int_y
    extern g_char_arr

    extern g_char_z
    extern g_int_arr
    extern g_char_str
    extern g_char_num
                              ; variables

    ;global g_some_asm_var
    ;extern g_some_c_var

;g_some_asm_var dd ?

;***************************************************************************

    section .text

    ; functions

    ;global some_asm_function
    ;extern some_c_function

    ; ex1

    global set_xy
set_xy:
    mov dword[ g_int_x ], 123456
    mov dword[ g_int_y ], 0x30313233
    ret

    global move_xz
move_xz:
    movsx eax, byte [g_char_z]
    mov[g_int_x], eax
    ret

    global set_arr
set_arr:
    mov dword [g_int_arr + 0 * 4], 12
    mov dword [g_int_arr + 1 * 4], 22
    mov dword [g_int_arr + 2 * 4], 32
    ret

    global set_text
set_text:
    mov [g_char_str + 0 * 4], byte "t"
    ret

    global write_to_arr
write_to_arr:
    movsx eax, byte [g_int_y]
    mov[g_char_arr], eax
    ret

    global switch_value
switch_value:
    mov eax, dword[g_int_x]
    mov ecx, dword[g_int_y]
    mov dword[g_int_x], ecx
    mov dword[g_int_y], eax
    ;; mov [ g_char_str + 0 ], byte "T"
    ;; mov [ g_char_str + 0 ], byte "T"
    ret

    global move_value
move_value:
    movsx eax, byte [g_char_num + 0]
    mov[g_int_x], eax
    movsx ecx, byte [g_char_num + 1]
    mov[g_int_y], ecx
    ret

    global set_x2
set_x2:
    mov dword[ g_int_x ], 0x01020304
    ret

    global switch_byte
switch_byte:
    mov eax, dword[g_int_x]
    bswap eax
    mov dword [g_int_x], eax
    ret


    ; ex2

    global sun
sum:
    enter 0,0
    mov eax, [ ebp + 8 ] ; parameter t_a
    add eax, [ ebp + 12 ] ; t_a += t_b
    leave
    ret
