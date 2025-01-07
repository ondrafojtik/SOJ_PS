//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Computing with Big Numbers
// Multiplication and Division
//
//***************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// t_a /= t_b; return t_a % t_b
int div_intNint32( int *t_a, int t_b, int t_N );

// t_a += t_b 
void add_intNint32( int *t_a, int t_b, int t_N );

// t_a *= t_b
void mul_intNint32( int *t_a, int t_b, int t_N );

// t_a += t_b
void add_intNintN( int *t_a, int *t_b, int t_N );

// t_a -= t_b
void sub_intNintN( int *t_a, int *t_b, int t_N );

// t_n <<= 1; return CF;
int shl_intN( int *t_n, int t_N );

// t_n >>= 1; return CF
int shr_intN( int *t_n, int t_N );

// t_n >>>= 1; return CF
int ror_intN( int *t_n, int t_N );

// t_n >>= cl <0,31>; return lost bits
int shrd_intN( int *t_n, int cl, int t_N );

// t_n <<= cl <0,31>; return lost bits
int shld_intN( int *t_n, int cl, int t_N );

// intN to string
void intN_to_str( int *t_n, int t_N, char *t_str );
// string to intN
void str_to_intN( char *t_str, int *t_n, int t_N );

// t_a /= t_b, t_b = remainder
void div_intNintN( int *t_a, int *t_b, int t_N );
// t_a *= t_b
void mul_intNintN( int *t_a, int *t_b, int t_N );
// is zero? ( t_n == 0 )
// return t_n == 0
int is_zero( int *t_n, int t_N )
{
  int i = 0;
  while ( i < t_N ) if ( t_n[ i++ ] ) return 0;
  return 1;
}

// compare of two intN numbers
// t_a >  t_b return  1
// t_a == t_b return  0
// t_a <  t_b return -1
int cmp_intNintN( int *t_a, int *t_b, int t_N )
{
  int i;
  for ( i = t_N - 1; i >= 0; i-- )
  {
      if ( t_a[ i ] == t_b[ i ] ) continue;
      if ( ( unsigned int ) t_a[ i ] > ( unsigned int ) t_b[ i ] ) return 1;
      return -1;
  }
  return 0;
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
  static int init_rand = 1;
  if ( init_rand ) srand( getuid() );

  for ( ; i < t_N; i++ )
    t_str[ i ] = rand() % 10 + '0';

  t_str[ i ] = 0;
}

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

  //printf( "Content of array (low first):\n" );
  //for ( ; i < t_N; i++ )
  //    printf( "%d ", t_n[ i ] );

  //printf( "\n\n" );
}

int main()
{
  int l_bin_a[ N_INT ] =
    { 0xabcd, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 2^255
  int l_bin_b[ N_INT ] =
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }; // 2^256
  int divisor[ N_INT ] =
    { 1000000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 10^9

  int l_bin_ran[ N_INT ];
  char l_str_ran[ N_CHAR ];

  printf( "\nBig number computing example.\n" );
  printf( "Computing with assigned numbers\n\n" );
  printf( "Numbers multiplication:\n\n" );

  mul_intNintN( l_bin_a, l_bin_b, N_INT );
  print_number( l_bin_a, N_INT );

  printf( "Press <Enter>\n" );
  getchar();

  get_random( l_str_ran, 100 );
  printf( "Computing with random number:\n\n" );

  printf( "Division of numbers\n\n" );

  str_to_intN( l_str_ran, l_bin_ran, N_INT );
  print_number( l_bin_ran, N_INT );

  div_intNintN( l_bin_ran, divisor, N_INT );

  printf( "Result of division:\n" );
  print_number( l_bin_ran, N_INT );

  printf( "Remainder:\n" );
  print_number( divisor, N_INT );

  return 0;
}

