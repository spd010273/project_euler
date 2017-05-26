/*
The primes 3, 7, 109, and 673, are quite remarkable.
By taking any two primes and concatenating them in any order
the result will always be prime. For example,
taking 7 and 109, both 7109 and 1097 are prime.
The sum of these four primes, 792, represents the lowest sum for
a set of four primes with this property.

Find the lowest sum for a set of five primes
for which any two primes concatenate to produce another prime.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int is_prime( unsigned long n )
{
    if( n == 2 || n == 3 )
    {
        return 1;
    }

    if( ( n % 2 == 0 ) || ( n % 3 == 0 ) )
    {
        return 0;
    }

    unsigned long i;
    unsigned long ceil = ( ( unsigned long ) sqrt( n ) + 2 );

    for( i = 6; i < ceil; i = i + 6 )
    {
        if( n % ( i - 1 ) == 0 )
        {
            return 0;
        }

        if( n % ( i + 1 ) == 0 )
        {
            return 0;
        }
    }

    return 1;
}

unsigned long concatenate_numbers( unsigned long a, unsigned long b )
{
    int a_length = floor( log10( (float) a ) ) + 1;
    int b_length = floor( log10( (float) b ) ) + 1;
    int length   = a_length + b_length;

    if( length == 1 )
    {
        if( a_length == 1 )
        {
            return a;
        }

        return b;
    }

    unsigned long * array = ( unsigned long * ) malloc( sizeof( unsigned long ) * length );

    if( &array == 0 )
    {
        printf( "Out of memory\n" );
        return 0;
    }

    int i = 0;
    
    while( b != 0 )
    {
        array[i] = b % 10;
        b /= 10;
        i++;
    }

    while( a != 0 )
    {
        array[i] = a % 10;
        a /= 10;
        i++;
    }

    int x = 1;
    i = 0;

    unsigned long out = 0;

    while( i < length )
    {
        out += array[i] * x;
        x *= 10;
        i++;   
    }

    free( array );

    return out;
}

int check_array( unsigned long * array )
{
    int i;

    for( i = 0; i < 5; i++ )
    {
        int j;

        for( j = i + 1; j < 5; j++ )
        {
            //printf( "I: %d J: %d i_val: %lu j_val: %lu\n", i, j, array[i], array[j] );
            if( 0 == is_prime( concatenate_numbers( array[i], array[j] ) ) ) return 0;
            if( 0 == is_prime( concatenate_numbers( array[j], array[i] ) ) ) return 0;
        }
    }

    return 1;
}

int fill_array( unsigned long * array )
{

}

int main()
{
    unsigned long * array = ( unsigned long * ) malloc( 5 * sizeof( unsigned long ) );
    array[0] = 3;
    array[1] = 7;
    array[2] = 109;
    array[3] = 673;
    array[4] = 1;

    if( check_array( array ) == 1 )
    {
        printf( "Array checks out!\n" );
    }

    return 0;
}
