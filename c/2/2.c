#include <stdio.h>

int main()
{
    int a   = 2;
    int b   = 1;
    int sum = 0;

    while( a < 4000000 )
    {
        if( a % 2 == 0 )
        {
            sum = sum + a;
        }

        a = a + b;
        b = a - b;
    }

    printf( "%d\n", sum );
    return 0;
}
