//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>

// Functions
// void some_asm_function();

// Variables
// type g_some_c_variable;

int num0(long t_num);
int num1(long t_num);
int nejvetsi(long* t_array, int size);
int test(long* t_num, int size);

long str2long(char* tp_strnum);

long str2long2(char* tp_strnum);


int main()
{
    //long number = 0xFFFFFFFFFFFFFFFF;
    long number = 0x0F000000000000FF;
    printf("num0: %d\n", num1(number));

    long l_array[4] = { 0x0FFFFFFFFF0000FF, 0x00000000000000FF, 0x00000000FFFFFFFF, 0x0FFFFFFFFF000000 };

    //printf("nejvetsi: %d\n", nejvetsi(l_array, 4));
    printf("test: %d\n", test(l_array, 4));

    char c2l[10] = "+123456789";
    printf("str2long: %ld\n", str2long(c2l));

    char c2l2[4] = "1221";
    printf("test: %ld\n", str2long2(c2l2));

}


    /*


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

.back1
    mov al, [rdi + r8]
    cmp al, 0
    je .done1

    inc r8
    loop .back1

.done1
    ; go back to 0
    dec r8

    cmp r8, 0                   ; sign at 0 -> last step
    je .done2

    ; alg
    mov al, [rdi + r8]
    sub rax, 48
    cbw
    cwd
    cdq

    mul r11
    add rax, r9

    mov r9, rax

    mov rax, r11
    imul rax, r10
    mov r11, rax

    loop .done1

.done2
    ; take care of sign
    mov al, [rdi + 0]
    cmp al, '+'
    je .done3

    jmp .done4

.done3
    mov rax, r9

    xor r10, r10
    xor r11, r11

    leave
    ret

.done4
    mov rax, r9
    imul rax, -1
    ;neg rax

    xor r10, r10
    xor r11, r11

    leave
    ret



    */
