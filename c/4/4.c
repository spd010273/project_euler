/*
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
/* compile with 'gcc 4.c -lm'*/

int is_pallindrome( unsigned long * x )
{
    unsigned long n = *x;

    int length  = floor( log10( (float) n ) ) + 1;
    int * array = ( int * ) malloc( length * sizeof( int ) );
    int i       = 0;

    while( n != 0 )
    {
        array[i] = n % 10;
        n /= 10;
        i++;
    }

    for( i = 0; i <= (int) ( ( length - 1 ) / 2 ); i++ )
    {
        if( array[i] != array[ length - 1 - i ] )
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    unsigned long test;
    // malloc a large array such that we can store our pallindromes
    // since the search algorithm is a naive loop, we'll have to locate the max later
    int MAX_SIZE            = 16; // probably the coolest power of 2 if i'm honest
    unsigned long * answers = ( unsigned long * ) malloc( MAX_SIZE * sizeof( unsigned long ) );
    int index               = 0;

    unsigned long i;
    unsigned long j;

    /*
        Completely arbitrary loop bounds, but it's an educated quess that:
            - We should start with high numbers and iterate down
            - Our largest palindromes will the multiples of something
              that starts with a 9 or 8
        To be pretty honest, we could slap on our thinking caps and come up with
        a sieve if we really wanted to.
    */

    for( i = 999; i > 900; i-- )
    {
        for( j = 999; j > 900; j-- )
        {
            test = i * j;

            if( is_pallindrome( &test ) == 1 )
            {
                //Hey, look at that! A pallindrome!
                answers[index] = test;
                index++;

                if( index >= MAX_SIZE )
                {
                    printf( "Not going to malloc more space because I'm lazy m80\n" );
                }

                // printf( "%lu * %lu = %lu\n", i, j, test );
            }
        }
    }

    unsigned long max = 0;

    // Look for the max pallindrome in our array
    for( i = 0; i < MAX_SIZE; i++ )
    {
        if( answers[i] > max )
        {
            max = answers[i];
        }
    }

    printf( "Max is %lu index used: %d\n", max, index );

    return 0;
}
