#include <stdio.h>
#include <math.h>

int is_prime( unsigned long * x )
{
    unsigned long n = *x;

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

int main()
{
    unsigned long n = 600851475143;
    unsigned long i;
    unsigned long * ptr;
    ptr = &i;    
    unsigned long ceil = (unsigned long) (sqrt( n )) + 2;
    for( i = ceil; i > 2; i-- )
    {
        if( ( n % i == 0 ) && is_prime( ptr ) )
        {
            printf( "%lu\n", *ptr );
            return 0;
        }
    }

    return 0;
}
