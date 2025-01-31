/***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Functions
// void some_asm_function();

// Variables
// type g_some_c_variable;

int sum (int a, int b);
int negative ( int * t_array , int t_N );
int odd(int* t_array, int t_N);
int num_of_even(int* t_array, int t_N);
long long decode(long long psw);
int test(short* t_array, int t_N);

int g_x, g_y;
int g_pole[4];
char g_str[] = "Ahoj.";
char g_c = -1;
int g_ic;


void first_fun();
void init_pole();
void uprav_str();
void prohod();
void c2ic();


/*
ZADANI
1) rozsirte g_c na 4 prvky a g_ic taky na 4 prvky g_c inicializujte na cisla kladna i raporna a preneste obsah g_c
2) vsechny prvky z pole g_ic zbavte nejnizsi jednicky (vynuljte spodni bit) -- AND
3) sectete prvky g_c a do int a g_ic take do int
4) vytvorte si retezec jen s malymi pismeny, delky max. 5 Pomoci aritmeticke operace prevedte mala na velka
5) zakodujte si do int cisla 4 znaky jako 0x31323334 cislo, preneste jej do retezce a vypiste

EAX, ECX, EDX

*/

char g_c2[4] = {1, -1, 9, -3};
int g_ic2[4] = {0, 0, 0, 0};
int g_c2_sum = 0;
int g_ic2_sum = 0;
char g_text[] = "test";


int g_cislo_i = 0x65727974;
char g_cislo_c[] = "....";

void jedna();
void dva();
void tri();
void ctyri();
void pet();


int suma_pole(int* t_pole, int t_N);
int hledej_min(int* t_pole, int t_N);
int pocet_mezer(char* t_str);

// CVICENI 2
/*
1) Napiste funkci, ktera najde minimum i maximum.
void minmax(int* t_pole, int N, int* minmax)

2) Napiste funkci, ktera vydeli vsechny prvky pole hodnotou 2^B^ (bitovy posun)
void deleni(int* t_pole, int N, int B);

3) Napiste funkci, ktera spocita pocet lichych cisel, kde posledni prvek pole je -1,
int lichych(int* t_pole);

4) Napiste funkci, ktera smaze mezery na konci retezce.
int bezkoncovych(char* t_str);

*/

void minmax(int* t_pole, int N, int* minmax);
void deleni(int* t_pole, int N, int B);
int lichych(int* t_pole);
int bezkoncovych(char* t_str);

// CVICENI 3

long long soucetll(long long a, long long b);
long long imul_ii(int a, int b);
long long idiv_lli(long long a, int b);
int idiv_ii(int a, int b); // return a/b

/*
1) provedte soucet prvku pole char do int bez preteceni
int suma_c_do_i(char* pole, int N);
char pole[] = {-100, -100, -100, -100, -100, -100, -100, -100, -100, -100};
char pole[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
int suma = 0;
suma += pole[i];

2) upravte soucet_ll na soucet_lli (long long + int -- znamenkove rozsireni int hodnoty)

3) sectete pole int bez preteceni, tedy do long long

4) napiste funkci s promennym poctem parametru, kde budou jen cistal int a sectete je. Posledni bude -1.

5) zjistete delku retezce ale pouzijte mov eax[reg] -> nacitat po 4
pouzitim operaci rypu ROL/ROR, SHR/SHL, loopnz/loopz si zkuste poradit

 */

int suma_c_do_i(char* pole, int N);
int suma_c_do_i2(char* pole, int N);
long long soucet_lli_upravene(long long a, int b);
long long soucet_int_pole(int* pole, int N);
int vatest(int n, ...);

// CVICENI 4 ?

long long atoi__(char* input);

int main()
{
    printf("***********************************\n");
    printf("***********************************\n");
    printf("***********************************\n");

    char input[] = "4234567890";
    long long result = atoi__(input);
    printf("atoi: %lld\n", result);


    /*
    //char pole[] = {100, 100, 100, 100, 100};
    char pole[] = {-100, -100, -100, -100, -100};
    printf("suma_c_do_i: %d\n", suma_c_do_i(pole, 5));
    printf("dva: %lld\n", soucet_lli_upravene(2000000000, 1));
    int i_pole[] = {1000000000, 1000000000, 1000000000};
    //int i_pole[] = {1, 2, 3};
    printf("tri: %lld\n", soucet_int_pole(i_pole, 3));


    int p[] = {1, 2, 3, 4, -1, 7, 6};
    int result = vatest2(p);
    printf("vatest %d\n", result);


    int m;
    m = vatest(1,2,3,4,-1);
    printf("vatest: %d\n",m);



    // EAX-EDX (kde EDX je vyzsi rad)
    printf("soucetll: %lld \n", soucetll(2000000000, 2000000000));
    printf("soucetll: 0x%llx \n", soucetll(0xFFFFFFFFFFFF, 1));
    printf("imul_ii %lld\n", imul_ii(1234567, 1000000));
    //printf("idiv_lli %d\n", idiv_lli(100000000000, 1000000));
    printf("idiv_ii: %d\n", idiv_ii(123456789, 1000));
    printf("idiv_ii: %d\n", idiv_ii(-123456789, 1000));
    */
    // printf(char* p, ...) -- man va_arg

    // m182

    /*
    int l_pole[10] = {100, 20, 30, -50, 50, 60, 70, 80, 150, 10};
    printf("SOUCET %d\n", suma_pole(l_pole, 10));
    printf("MIN %d\n", hledej_min(l_pole, 10));
    char l_str[] = " A H o J . ";
    printf("POCETMEZER %d\n", pocet_mezer(l_str));
    int l_minmax[2] = {0, 0};
    minmax(l_pole, 10, l_minmax);
    printf("min: %d, max: %d\n", l_minmax[0], l_minmax[1]);
    int l_pole2[4] = {-4, 8, 12, 16};
    deleni(l_pole2, 4, 2);
    for (int i = 0; i < 4; i++)
        printf("%d ", l_pole2[i]);
    printf("\n");
    int l_pole3[4] = {1, 2, 0x03030303, -1};
    printf("pocet licych: %d\n", lichych(l_pole3));
    char l_str2[] = "Ah oj    ";
    printf("%d\n", bezkoncovych(l_str2));
    printf("%d\n", strlen(l_str2));
    printf("***********************************\n");
    printf("***********************************\n");
    printf("***********************************\n");
    */
    /*

    first_fun();
    printf("%d \n", g_x);
    printf("%x \n", g_y);

    init_pole();
    for (int i = 0; i < 4; i++)
        printf("%i \n", g_pole[i]);

    uprav_str();
    printf("%s\n", g_str);

    prohod();
    printf("%x \n", g_x);
    printf("%d \n", g_y);

    c2ic();
    printf("%d\n", g_c);
    printf("%d\n", g_ic);


    printf("***********************************\n");
    printf("***********************************\n");
    printf("***********************************\n");


    jedna();
    for (int i = 0; i < 4; i++)
        printf("%d   ", g_ic2[i]);
    printf("\n");

    dva();
    for (int i = 0; i < 4; i++)
        printf("%d   ", g_ic2[i]);
    printf("\n");

    tri();
    printf("%d   ", g_c2_sum);
    printf("%d   ", g_ic2_sum);
    printf("\n");

    printf("%s \n", g_text);
    ctyri();
    printf("%s \n", g_text);

    char t[] = "AHOJ";
    for (int i = 0; i < 4; i++)
        printf("%d", t[i]);
    printf("\n");

    pet();
    printf("%d \n", g_cislo_i);
    printf("%s \n", g_cislo_c);


    printf("***********************************\n");
    printf("***********************************\n");
    printf("***********************************\n");


    int l_pole[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int l_pole_[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int l_pole__[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int l_N = 10;
    // otocit vsechna znamenka bez pouziti NEG
    // upravit vsechna cisla v poli na licha
    // spocitejte kolik je v poli sudych cisel
    //
    printf("base\n");
    for(int i = 0; i < l_N; i++)
        printf("%i, ", l_pole[i]);
    printf("\n");

    printf("negative\n");
    negative(l_pole, l_N);
    for(int i = 0; i < l_N; i++)
        printf("%i, ", l_pole[i]);
    printf("\n");

    odd(l_pole_, l_N);
    printf("sude\n");
    for(int i = 0; i < l_N; i++)
        printf("%i, ", l_pole_[i]);
    printf("\n");

    int num_even = num_of_even(l_pole__, l_N);
    printf("num_of_even: %i\n", num_even);
    printf("verification\n");
    for (int i = 0; i < l_N; i++)
        printf("%i, ", l_pole__[i]);
    printf("\n");
    // 0x8f9eac8c88cf8d9b
    short psw[5] = {0x8f9e, 0xac8c, 0x88cf, 0x8d9b, 0};
    test(psw, 4);
    printf("%s\n", (char*)psw);
    */

    /*--5-----------------------------------------------
    Převeďte číslo na hex string.
    void nahex( int t_num, char *t_str, char *t_prevod ),
    kde t_prevod bude "0123456789ABCDEF".

    for ( int i = 0; i < 8; i++ )
      t_str[ 7 - i ] =  t_prevod[ t_num & 0xF ]
      t_num >>= 4       // shr reg, 4

    ----5---------------------------------------------*/




}
