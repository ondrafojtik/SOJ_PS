//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>

#define EX1 1
#define EX2 0

// Functions
// void some_asm_function();

// Variables
// type g_some_c_variable;

// extern says there is something
// static == private

// test je kod

// g++ foo.c c-main.c -o output

// ex1

char g_char_z = -1;
int g_int_arr[3];
char g_char_str[] = "Tohle";
void move_xz();
void set_arr();
void set_text();

// EAX, ECX, EDX

int g_int_x;
int g_int_y;
char g_char_arr[5] = ".....";
char g_char_num[2] = {-100, 100};

void set_xy();
void set_x2();
void write_to_arr();
void switch_value();
void move_value();
void switch_byte();

// ex2
#if EX2
void foo(int a, int b, int c)
{
    printf("%i, %i, %i\n", a, b, c);
}

int sun(int a, int b);
#endif

int main()
{

    // ex1
#if EX1
    // 1
    set_xy();
    //move_xz();
    printf("x: %i \n", g_int_x);
    printf("y: %x \n", g_int_y);

    //printf("testtttttt\n");
    //set_arr();
    //for (int i = 0; i < 3; i++)
    //    printf("%i\n", g_int_arr[i]);

    //set_text();
    //printf("%s", g_char_str);


    // 2 ????
    write_to_arr();
    for (int i = 0; i < 5; i++)
        printf("%c", g_char_arr[i]);
    printf("\n");

    // 3
    switch_value();
    printf("x_switch: %i \n", g_int_x);
    printf("y_switch: %i \n", g_int_y);

    // 4
    move_value();
    printf("x_from_arr: %i \n", g_int_x);
    printf("y_from_arr: %i \n", g_int_y);


    // 5
    set_x2();
    printf("byte_switch: %x \n", g_int_x);
    switch_byte();
    printf("byte_switch: %x \n", g_int_x);

#endif

    // ex2
#if EX2
    printf("hello\n");

    // jede se zprava na stacku se to uklada takhle..
    int i__ = 0;
    foo(i__++, i__++, i__++);
#endif
    // OPERACE
    // ADD cil, zdroj
    // cil = CIL OP ZDROJ
    // OP = AND(&), OR(|), XOR(^), ADD(+), SUB(-)
    // NOT cil - negace (v C je to ~)
    // NEG cil - otoceni znamenka (vcetne dvojkoveho doplnku)
    // INC - increment (i++)

    // SKOKY
    // CALL - volani funkce (my budeme delat v C)
    // JMP cil -
    // LOOP cil - zabere ECX (counter)
    //          - loop jede z druhe strany -> od N do 1 (misto 0->n-1)
    // JCXZ -> skok pryc kdyz je nulovy (aby nebyl inf loop)


}
