/*
The number 3797 has an interesting property. Being prime itself,
it is possible to continuously remove digits from left to right,
and remain prime at each stage: 3797, 797, 97, and 7.
Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable
from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int MAX = 10000000;

int is_prime( unsigned long n )
{
    if( n <= 1 )
    {
        return 0;
    }

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

int is_truncatable_prime( unsigned long x )
{
    if( is_prime( x ) == 0 )
    {
        return 0;
    }
    
    int length = floor( log10( (float) x ) ) + 1;

    int * array = ( int * ) malloc( sizeof( int ) * length );
    if( &array == 0 )
    {
        printf( "Out of memory\n" );
        return 0;
    }

    int i = 0;

    while( x != 0 )
    {
        array[i] = x % 10;
        x /= 10;
        i++;
    }

    int j; // inner index
    int y = 1;
    unsigned long check_num = 0;

    // from left
    for( i = 0; i < length; i++ )
    {
        for( j = i; j < length; j++ )
        {
            check_num += array[j] * y;
            y *= 10;
        }
        
        if( 0 == is_prime( check_num ) )
        {
            return 0;
        }

        y = 1;
        check_num = 0;
    }

    y = 1;
    check_num = 0;

    // from right
    for( i = 0; i < length; i++ )
    {
        for( j = 0; j <= i; j++ )
        {
            check_num += array[j] * y;
            y *= 10;
        }
        
        if( 0 == is_prime( check_num ) )
        {
            return 0;
        }

        y = 1;
        check_num = 0;
    }
    
    free( array );
    return 1;
}

unsigned long * generate_primes( int * pc )
{
    int prime_count = 0;
    int upper_bound = (int) sqrt( MAX );
    int * composite_bitmap = ( int * ) malloc( sizeof( int ) * ( MAX + 1 ) );
    int i;

    for( i = 0; i < MAX; i ++ )
    {
        composite_bitmap[i] = 0;
    }
    
    int m;

    for( m = 2; m <= upper_bound; m++ )
    {
        if( composite_bitmap[m] == 0 )
        {
            prime_count++;
            int k;
            for( k = m*m; k <= MAX; k += m )
            {
                composite_bitmap[k] = 1 ;
            }
        }
    }

    for( m = upper_bound; m <= MAX; m++ )
    {
        if( composite_bitmap[m] == 0 )
        {
            prime_count++;
        }
    }

    unsigned long * array = ( unsigned long * ) malloc( sizeof( unsigned long ) * prime_count );
    prime_count = 0;
    for( i = 0; i < MAX; i++ )
    {
        if( composite_bitmap[i] == 0 )
        {
            array[prime_count] = i;
            prime_count++;
        }
    }

    free( composite_bitmap );
    * pc = prime_count;
    return array;
}

int main()
{
    int prime_count = 0;
    unsigned long * array = generate_primes( &prime_count ); 
    if( &array == 0 )
    {
        printf( "Failed to allocate memory for prime array\n" );
        return 0;
    }


    int tprime_count = 0;
    unsigned long sum = 0;
    int prime_index = 0;
    
    while( tprime_count < 11 )
    {
        if(
               array[prime_index] > 10
            && is_truncatable_prime( array[prime_index] ) == 1
          )
        {
            tprime_count++;
            sum += array[prime_index];

            printf( "Found truncatable prime: %lu\n", array[prime_index] );
        }

        prime_index++;

        if( prime_index >= prime_count )
        {
            printf( "Array bounds exceeded PI: %d of %d\n", prime_index, prime_count );
            break;
        }
    }

    free( array );
    
    printf( "Sum of %d truncatable primes is %lu\n", tprime_count, sum );
    return 1;
}
