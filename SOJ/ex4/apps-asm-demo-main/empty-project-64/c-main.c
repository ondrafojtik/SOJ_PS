//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#define N_INT   16
#define N_CHAR  ( N_INT * 32 * 3 / 10 + 2 )


#include <stdio.h>
#include <stdint.h>

// return t_n == 0
int is_zero( int *t_n, int t_N )
{
  int i = 0;
  while ( i < t_N ) if ( t_n[ i++ ] ) return 0;
  return 1;
}

// t_a += t_b
void add_intNintN( int *t_a, int *t_b, int t_N );

// t_a -= t_b
void sub_intNintN( int *t_a, int *t_b, int t_N );

// t_n <<= 1; return CF;
int shl_intN( int *t_n, int t_N );

// t_n >>= 1; return CF
int shr_intN( int *t_n, int t_N );

// intN to string in hexadecimal form
void intN_to_hex( int *t_n, int t_N, char *t_str )
{
   int i = 0;
   for ( ; i < t_N; i++, t_str+= 8 )
       sprintf( t_str, "%08X", t_n[ t_N - i - 1 ] );
}


// t_a += t_b
void add_intNint32( int *t_a, int t_b, int t_N );

// t_a *= t_b
void mul_intNint32( int *t_a, int t_b, int t_N );

// t_a /= t_b, return reminder
int div_intNint32( int *t_a, int t_b, int t_N );


// intN to string
void intN_to_str( int *t_n, int t_N, char *t_str )
{
    int* result = malloc(t_N * sizeof(int));
	memcpy(result, t_n, t_N * sizeof(int));

	int len = 0;
	char* str_ = t_str;

	do
	{
		*str_++ = div_intNint32(result, 10, t_N) + '0';
	    len++;
	}
	while (!is_zero(result, t_N));

	*str_ = '\0';

	for (int i = 0; i < len / 2; i++)
	{
		char tmp = t_str[i];
		t_str[i] = t_str[len - 1 - i];
		t_str[len - 1 - i] = tmp;
	}

	free(result);
}

// string to intN
void str_to_intN( char *t_str, int *t_n, int t_N )
{
    memset(t_n, 0, sizeof(int) * t_N);

	while (*t_str)
	{
		mul_intNint32(t_n, 10, t_N);
		add_intNint32(t_n, *t_str - '0', t_N);
		t_str++;
	}
}

// random number
void get_random( char *t_str, int t_N )
{
  int i = 0;
  static int init_rand = 1;
  if ( init_rand ) srand( getuid() );

  for ( ; i < t_N; i++ )
    t_str[ i ] = rand() % 10 + '0';

  t_str[ i ] = 0;
}


void print_number( int *t_n, int t_N )
{
  char l_str_number[ N_CHAR ];
  int i = 0;

  intN_to_hex( t_n, t_N, l_str_number );
  printf( "Hexadecimal number:\n%s\n\n", l_str_number );

  intN_to_str( t_n, N_INT, l_str_number );
  printf( "Decimal number:\n%s\n\n", l_str_number );

  //printf( "Content of array (low first):\n" );
  //for ( ; i < t_N; i++ )
  //    printf( "%d ", t_n[ i ] );
  //
  //printf( "\n\n" );
}

int compare_Htb(int* t_a, int* t_b, int t_N)
{
    for (int i = t_N - 1; i >= 0; i--)
    {
        uint32_t a = t_a[i];
        uint32_t b = t_b[i];

        if (a > b) return 1;
        if (a < b) return 0;
    }

    return 1; // H >= t_b
}


// t_a /= t_b, t_b = remainder
void div_intNintN( int *t_a, int *t_b, int t_N )
{

    printf("A--------\n");
    print_number(t_a, t_N);
    printf("B--------\n");
    print_number(t_b, t_N);

    int* result = malloc(t_N * sizeof(int) * 2);

    // clear
    for (int i = 0; i < t_N * 2; i++)
	    result[i] = 0;

	// prekopirovani delence
	int* divident = malloc(t_N * 2 * sizeof(int));
	for (int i = 0; i < t_N * 2; i++)
	{
        divident[i] = 0;
        if (i < t_N)
            divident[i] = t_a[i];
    }

	int* H = divident + t_N;

	for (int i = 0; i < t_N * sizeof(int) * 8; i++)
	{
		shl_intN(result, t_N * 2);
		shl_intN(divident, t_N * 2);

        if (compare_Htb(H, t_b, t_N))
        {
			*result |= 1;
			sub_intNintN(H, t_b, t_N);
		}
	}

    //printf("RESULT-------------\n");
    //print_number(result, t_N);

    // copy
    for (int i = 0; i < t_N; i++)
    {
        t_a[i] = result[i];
        t_b[i] = H[i];
    }

	free(divident);
    free(result);
}

// t_a *= t_b
void mul_intNintN( int *t_a, int *t_b, int t_N )
{
    int* result = malloc(t_N * sizeof(int));

    // clear
    for (int i = 0; i < t_N; i++)
	    result[i] = 0;


    printf("A--------\n");
    print_number(t_a, t_N);
    printf("B--------\n");
    print_number(t_b, t_N);

    // alg
    while (!is_zero(t_b, t_N))
	{
		if (*t_b & 1)
	    	add_intNintN(result, t_a, t_N);

		shl_intN(t_a, t_N);
		shr_intN(t_b, t_N);
	}

    // copy
    for (int i = 0; i < t_N; i++)
        t_a[i] = result[i];

    //printf("VYSLEDEK----------------\n");
    //print_number(t_a, t_N);
    //printf("------------------------\n");

    free(result);

}


int main()
{
    int l_bin_a[ N_INT ] =
    { 0xabcd, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
    int l_bin_b[ N_INT ] =
    { 0x0002, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int divisor[ N_INT ] =
    { 1000000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    //printf("test-------------------\n");
    //add_intNintN(l_bin_a, l_bin_b, N_INT);
    //print_number(l_bin_a, N_INT);
    //sub_intNintN(l_bin_a, l_bin_b, N_INT);
    //sub_intNintN(l_bin_a, l_bin_b, N_INT);
    //print_number(l_bin_a, N_INT);

    int l_bin_ran[ N_INT ];
    char l_str_ran[ N_CHAR ];

    printf( "\nBig number computing example.\n" );
    printf( "Computing with assigned numbers\n\n" );
    printf( "Numbers multiplication:\n\n" );

    //printf("a-------------------------\n");
    //print_number(l_bin_a, N_INT);
    //printf("b-------------------------\n");
    //print_number(l_bin_b, N_INT);


    printf("MUL--------------------\n");
    mul_intNintN( l_bin_a, l_bin_b, N_INT );
    print_number( l_bin_a, N_INT );
    printf("MUL-----------------END\n");

    printf( "Press <Enter>\n" );
    getchar();

    get_random( l_str_ran, 100 );
    printf( "Computing with random number:\n\n" );

    printf( "Division of numbers\n\n" );

    str_to_intN( l_str_ran, l_bin_ran, N_INT );
    print_number( l_bin_ran, N_INT );

    int l_bin_c[ N_INT ] =
    { 1000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    printf("DIV--------------------\n");
    div_intNintN(l_bin_a, l_bin_c, N_INT);
    printf("DIV-----------------END\n");

    printf( "Result of division:\n" );
    //print_number( l_bin_ran, N_INT );
    print_number(l_bin_a, N_INT);

    printf( "Remainder:\n" );
    //print_number( divisor, N_INT );
    print_number(l_bin_c, N_INT);

    return 0;


}
