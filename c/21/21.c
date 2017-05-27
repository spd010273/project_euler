/*
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000
*/
#include <stdio.h>
#include <math.h>

int sum_divisors( int x )
{
    int n;
    int ceil = ( (int) x / 2 ) + 1;
    int divisor_sum = 1;

    for( n = 2; n < ceil; n++ )
    {
        if( x % n == 0 )
        {
            divisor_sum += n;
        }
    }

    return divisor_sum;
}

int is_amicable_number( int a )
{
    int b = sum_divisors( a );

    if( sum_divisors( b ) == a && a != b )
    {
        printf( "Found amiacable number %d %d\n", a, b );
        return 1;
    }

    return 0;
}

int main()
{
    int i;
    unsigned long sum = 0;
    
    for( i = 0; i <= 10000; i++ )
    {
        if( 1 == is_amicable_number( i ) )
        {
            sum += i;
        }
    }

    printf( "Sum is %lu\n", sum );

    return 0;
}
