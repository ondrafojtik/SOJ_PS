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


int soucet(int* tp_j, int* tp_d, int* tp_v, int len);


int main()
{
    int j[3] = {1, 2 ,3};
    int d[3] = {3, 2, 12};
    int v[3] = {0, 0, 0};

    printf("test: %d\n", soucet(j, d, v, 3));
    for (int i = 0; i < 3; i++)
        printf("%d ,", v[i]);
    printf("\n");

}
