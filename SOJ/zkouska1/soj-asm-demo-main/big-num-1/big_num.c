//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Computing with Big Numbers
//
//***************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// t_a += t_b
void add_intNint32( int *t_a, int t_b, int t_N );

// t_a *= t_b
void mul_intNint32( int *t_a, int t_b, int t_N );

// t_a /= t_b, return reminder
int div_intNint32( int *t_a, int t_b, int t_N );

void intN_to_str( int *t_n, int t_N, char *t_s );
void str_to_intN( char *t_str, int *t_n, int t_N );

// return t_n == 0
int is_zero( int *t_n, int t_N )
{
  int i = 0;
  while ( i < t_N ) if ( t_n[ i++ ] ) return 0;
  return 1;
}

// intN to string in hexadecimal form
void intN_to_hex( int *t_n, int t_N, char *t_str )
{
   int i = 0;
   for ( ; i < t_N; i++, t_str+= 8 )
       sprintf( t_str, "%08X", t_n[ t_N - i - 1 ] );
}

// random number
void get_random( char *t_str, int t_N )
{
  int i = 0;
  srand( getuid() );

  for ( ; i < t_N; i++ )
    t_str[ i ] = rand() % 10 + '0';

  t_str[ i ] = 0;
}

// function template for intN to string conversion
/*
void intN_to_str( int *t_n, int t_N, char *t_str )
{
  ...

  while ( !is_zero( t_n, t_N ) )
    t_str[ i++ ] = div_intNint32( ... ) + '0';

  ...
}*/

// function template for string to intN conversion
/*
void str_to_intN( char *t_str, int *t_n, int t_N )
{
  ...
  while ( *t_str )
  {
      mul_intNint32( ... );
      add_intNint32( ... );
  }
  ...
}
*/

#define N_INT   16
#define N_CHAR  ( N_INT * 32 * 3 / 10 + 2 )

void print_number( int *t_n, int t_N )
{
  char l_str_number[ N_CHAR ];
  int i = 0;

  intN_to_hex( t_n, t_N, l_str_number );
  printf( "Hexadecimal number:\n%s\n\n", l_str_number );

  intN_to_str( t_n, N_INT, l_str_number );
  printf( "Decimal number:\n%s\n\n", l_str_number );

  printf( "Content of array (low first):\n" );
  for ( ; i < t_N; i++ )
      printf( "%d ", t_n[ i ] );

  printf( "\n\n" );
}


int main()
{
  long long l_ll = 0xffffffff;
  int l_bin_number[ N_INT ] =
//    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80000000 }; // 2^511
    { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff }; // 2^511
  int l_ran_number_b[ N_INT ];
  char l_ran_number_a[ N_CHAR ];

  printf( "\nBig number computing example.\n" );
  printf( "%d bits numbers are used.\n\n", N_INT * 32 );

  printf( "Computing with assigned number\n\n" );

  mul_intNint32( l_bin_number, 0xffffffff, N_INT );
  print_number( l_bin_number, N_INT );

  printf( "Press <Enter>\n" );
  getchar();

  printf( "Computing with random number\n\n" );

  get_random( l_ran_number_a, 100 );
  printf( "Generated random number:\n\n%s\n\n", l_ran_number_a );

  str_to_intN( l_ran_number_a, l_ran_number_b, N_INT );
  print_number( l_ran_number_b, N_INT );

  return 0;
}

