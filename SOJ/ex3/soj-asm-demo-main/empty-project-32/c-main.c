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

void jedna(char* t_str, int t_N);
unsigned long dva(unsigned long t_a);
int tri(char* t_str, int t_N);
long long pet(char* t_str);
void ctyri(long* tp_a, long* tp_b, long* tp_c, int t_N);

int main()
{
    char text[4] = "AhOj";
    jedna(text, 4);
    printf("jedna: %s\n", text);

    //int b_mirror = 0x11111111;
    //printf("dva: %8lX\n", dva(b_mirror));

    char text_with_spaces[10] = "Az h o   j";
    tri(text_with_spaces, 10);
    printf("tri: %s\n", text_with_spaces);

    long j[3] = {10, 2, 3};
    long d[3] = {3, 23, 1};
    long t[3] = {0, 0, 0};
    ctyri(j, d, t, 3);
    for (int i = 0; i < 3; i++)
        printf("%ld, ", t[i]);
    printf("\n");

    printf("pet: %lld\n", pet("1 34c"));



}
