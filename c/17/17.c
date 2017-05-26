/*
If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?


NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
*/

#include <stdio.h>

int get_letter_count( int x )
{
    if( x == 0 ) return 0; // catchall
    if( x == 1 ) return 3; // one
    if( x == 2 ) return 3; // two
    if( x == 3 ) return 5; // three
    if( x == 4 ) return 4; // four
    if( x == 5 ) return 4; // five
    if( x == 6 ) return 3; // six
    if( x == 7 ) return 5; // seven
    if( x == 8 ) return 5; // eight
    if( x == 9 ) return 4; // nine
    if( x == 10 ) return 3; // ten
    if( x == 11 ) return 6; // eleven
    if( x == 12 ) return 6; // twelve
    if( x == 13 ) return 8; // thirteen
    if( x == 14 ) return 8; // fourteen
    if( x == 15 ) return 7; // fifteen
    if( x == 16 ) return 7; // sixteen
    if( x == 17 ) return 9; // seventeen
    if( x == 18 ) return 8; // eighteen
    if( x == 19 ) return 8; // nineteen
    if( x == 20 ) return 6; // twenty
    if( x == 30 ) return 6; // thirty
    if( x == 40 ) return 5; // forty
    if( x == 50 ) return 5; // fifty
    if( x == 60 ) return 5; // sixty
    if( x == 70 ) return 7; // seventy
    if( x == 80 ) return 6; // eighty
    if( x == 90 ) return 6; // ninety

    /*
        recursive section:
            Handle cases of
            1000 = one thousand + get_letter_count( <hundreds part> )

            IE we want the program flow to be:
            get_letter_count( 1234 )
                one thousand + get_letter_count( 234 )
                    two hundred and + get_letter_count( 34 )
                        thirty four

            get_letter_count( 2040 )
                two thousand + get_letteR_count( 40 )
                    fourty
    */
    if( x >= 1000 )
    {
        return get_letter_count( (int) x / 1000 ) + 8 + get_letter_count( x - ( (int) x / 1000 ) * 1000 );
    }

    if( x >= 100 )
    {
        // Handle conditional:
        // if we're at a rounded hundreds ( 100, 200, 300, etc)
        // Do not include the 'and <tens>' part
        if( ( x - ( (int) x / 100 ) * 100 ) > 0 )
        {
            return get_letter_count( (int) x / 100 ) + 7 + 3 + get_letter_count( x - ( ( int ) x / 100 ) * 100 );
        }

        return get_letter_count( (int) x / 100 ) + 7;
    }

    int tens = 10 * ( (int) x / 10 );
    return get_letter_count( tens ) + get_letter_count( x - tens );
}

int main()
{
    int letter_count = 0;
    unsigned long sum = 0;
    int i;

    for( i = 1; i <= 1000; i++ )
    {
        letter_count = get_letter_count( i );
        //printf( "LC: %d, i: %d\n", letter_count, i  );
        sum += letter_count;
    }

    printf( "Answer: %lu\n", sum );
    return 0;
}
