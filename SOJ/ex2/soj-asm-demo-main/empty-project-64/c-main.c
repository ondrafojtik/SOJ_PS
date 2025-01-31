//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>

// t_a += t_b
void add_intNint32( int *t_a, int t_b, int t_N );

// t_a *= t_b
void mul_intNint32( int *t_a, int t_b, int t_N );

// t_a /= t_b, return reminder
int div_intNint32( int *t_a, int t_b, int t_N );

// t_a += t_b
void add_intNintN( int *t_a, int *t_b, int t_N );

// t_a -= t_b
void sub_intNintN( int *t_a, int *t_b, int t_N );

// t_n <<= 1; return CF;
int shl_intN( int *t_n, int t_N );

// t_n >>= 1; return CF
int shr_intN( int *t_n, int t_N );

// t_a /= t_b, t_b = remainder
/*void div_intNintN( int *t_a, int *t_b, int t_N )
{
  int dividend[ 2 * t_N ];
  int *H = divident + t_N;
  divident = t_a
  for ( all_bits ... )
  {
      divident <<= 1
      res <<= 1
      if ( H >= t_b )
      {
          H -= t_b;
          res |= 1;
      }
  }
  ... store res-ult and remainder
}*/

// t_a *= t_b
/*void mul_intNintN( int *t_a, int *t_b, int t_N )
{
  res = 0
  for( all_bits.... )
  {
      if ( t_b is odd )
          res += t_a;
      t_a <<= 1;
      t_b >>= 1;
  }
  store res-ult...
}*/


void mul(int* t_a, int* t_b, int t_N)
{
    int l_c = 0;
    for (int i = 0; i < (4 * t_N); i++)
    {
        int number = (*t_b >> i) & 1;
        if (number == 1)
            l_c += *t_a;

        shl_intN(t_a, sizeof(t_a));
        shr_intN(t_b, sizeof(t_b));
        //printf("test: %d\n", number);
    }

    printf("vysledek: %lld\n", l_c);
}

float f2f(float t_a); // return t_a;
double d2d(double t_a); // return t_a;
float d2f(double t_a);
double f2d(float t_a);

double add_d(double t_a, double t_b);
float suma_f(float* tp_array, int t_N);
float prumer_f(float *tp_array, int t_N);
float min_f(float* tp_array, int t_N);
int in_range(float *tp_array, int t_N, float t_min, float t_max);
double abs_d(double t_d);

/* PRIKLADY

1) Vypocitejte cislo e s presnosti na 10E-5  -> e = 1 + 1/1! + 1/2! ... error = 1/n! - 1/(n-1)  ||  Vypocitat na SSE

2) Povrch a objem koule.

3) Uhlopricka obdelnika. (vyzkouseni odmocniny)

4) Tvori nejaka trojice sousednich cisel v poli provouhly trojuhelnik? (na vyzkouseni prace s polem)

*/


float povrch_koule(float t_a, float pi);
float objem_koule(float t_a, float pi);
float uhlopricka(float t_a, float t_b);
float ctyri(float* t_array, int t_N);
float ctyri_test(float* t_array, int t_N);

float factorial(float number);
float jedna(float number);

float factorial__(int n)
{
    float sum = 1;
    while (n != 1)
    {
        sum *= n;
        n -= 1;
    }
    return sum;
}

void test()
{
    int precision = 15;
    double e = 1;
    for (int i = 1; i < precision; i++)
    {
        float f = factorial__(i);
        e += 1/f;
    }

    printf("e: %f\n", e);
}


int main()
{
#if 0
    //test();

    //printf("factirial: %f\n", factorial(3));
    printf("jedna: %f\n", jedna(3));
    float trojuhelniky[10] = {3.0, 4.0, 5.0, 7.0, 17.0, 3.0, 4.0, 5.0, 17.0, 22.0};
    printf("uhlopricka: %f\n", uhlopricka(3, 4));
    printf("povrch_koule: %f\n", povrch_koule(10.0, 3.14));
    printf("objem_koule: %f\n", objem_koule(10.0, 3.14));
    printf("pocet trojuhelniku: %f\n", ctyri(trojuhelniky, (10-2)));
#endif
//float suma = 0; // nefunguje dobre, rychle "dojede" a pak se opakuje, obecne velmi spatny napad jakkoli porovnavat s int -> pocitani casu na float == zle || veliky problem treba u raket.. Patriot Missile problem
    //while(1)
    //{
    //    suma += 0.1;
    //    printf("suma: %f\n", suma);
    //}

#if 0
    float l_farray[10] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10};
    printf("abs_d %f\n", abs_d(10.0));
    printf("in_range: %d\n", in_range(l_farray, 10, 5, 8));
    printf("min_f %f\n", min_f(l_farray, 10));
    printf("suma_f %f\n", suma_f(l_farray, 10));
    printf("prumer_f %f\n", prumer_f(l_farray, 10));
    printf("f2f %f\n", f2f(3.14));
    printf("d2d %f\n", d2d(3.14));
    printf("f2d %f\n", f2d(3.14));
    printf("d2f %f\n", d2f(3.14));
    printf("add_d %f\n", add_d(3.14, 1000));
#endif


#if 1
	printf("hello test");
 		
    int a = 16;
    int b = 4;
    mul(&a, &b, sizeof(a));

    int test = 4;
    shl_intN(&test, sizeof(test));
    printf("shr: %d\n", test);


    long long add_a = 4000000000;
    int add_b = 2000000000;
    add_intNint32(&add_a, add_b, sizeof(add_a));
    printf("add: %lld\n", add_a);

    long long div_a = 32;
    int div_b = 8;
    div_intNint32(&div_a, div_b, sizeof(div_a));
    printf("div: %lld\n", div_a);

    long long mul_a = 4000000000;
    int mul_b = 4;
    mul_intNint32(&mul_a, mul_b, sizeof(mul_a));
    printf("mul: %lld\n", mul_a);


    long long add_intNa = 6000000000;
    long long add_intNb = 4000000000;
    add_intN_intN(&add_intNa, &add_intNb, sizeof(add_intNa));
    printf("add_intNintN: %lld\n", add_intNa);

    long long sub_intNa = 6000000000;
    long long sub_intNb = 4000000000;
    sub_intNintN(&sub_intNa, &sub_intNb, sizeof(sub_intNb));
    printf("sub_intNintN: %lld\n", sub_intNa);

#endif
    return 0;

}
