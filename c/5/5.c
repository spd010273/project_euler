/*
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/
#include <stdio.h>

int check_divisor( unsigned long x )
{
    if( x % 11 != 0 ) return 0;
    if( x % 12 != 0 ) return 0;
    if( x % 13 != 0 ) return 0;
    if( x % 14 != 0 ) return 0;
    if( x % 15 != 0 ) return 0;
    if( x % 16 != 0 ) return 0;
    if( x % 17 != 0 ) return 0;
    if( x % 18 != 0 ) return 0;
    if( x % 19 != 0 ) return 0;
    if( x % 20 != 0 ) return 0;
    return 1;
}

// Super naive solution where we simply brute force the number starting from 1 :|
int main()
{
    unsigned long n = 0;

    while( 1 )
    {
        n++;
        if( check_divisor( n ) == 1 )
        {
            printf( "Found smallest evenly divisible #: %lu\n", n );
            return 0;
        }
    }

    printf( "Better luck next time!\n" );
    return 1;
}

