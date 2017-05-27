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

typedef unsigned long long int t_item;

static t_item all_true = ~0LL;
static int BITS = sizeof( t_item );
static int MAX = 50000;
static int ARBITRARY_SIZE = 10000;
typedef struct {
    unsigned long       candidate;
    int                 is_prime;
} PrimeCacheElem;

typedef struct {
    PrimeCacheElem *    head;
    unsigned long       length;
} PrimeCache;

PrimeCache prime_cache;

int init_prime_cache()
{
    prime_cache.length = 1;
    prime_cache.head = ( PrimeCacheElem * ) malloc( sizeof( PrimeCacheElem ) ); 
    
    if( &(prime_cache.head) == 0 )
    {
        printf( "Failed to initialize cache\n" );
        return 0;
    }
    
    prime_cache.head[0].candidate = 2;
    prime_cache.head[0].is_prime = 1;
    
    return 1;
}

int expand_prime_cache()
{
    PrimeCacheElem * current_cache = prime_cache.head;
    prime_cache.head = ( PrimeCacheElem * ) malloc( ( prime_cache.length + 1 ) * sizeof( PrimeCacheElem ) );
    
    if( &(prime_cache.head) == 0 )
    {
        free( current_cache );
        return 0;
    }
    
    // copy over values, free old list
    int i;
    
    for( i = 0; i < prime_cache.length; i++ )
    {
        prime_cache.head[i].candidate = current_cache[i].candidate;
        prime_cache.head[i].is_prime  = current_cache[i].is_prime;
    }

    free( current_cache );
    prime_cache.length += 1;
    
    return 1;
}

int check_cache( unsigned long val )
{
    if( val < ARBITRARY_SIZE )
    {
        return 2;
    }
 
    int len = prime_cache.length;
    int i;

    for( i = 0; i < prime_cache.length; i++ )
    {
        if( prime_cache.head[i].candidate == val )
        {
            return prime_cache.head[i].is_prime;
        }
    }

    return 2;
}

int add_to_cache( unsigned long val, int is_prime )
{
    if( val < ARBITRARY_SIZE )
    {
        return 0;
    }

    if( expand_prime_cache() == 0 )
    {
        printf( "Failed\n" );
        return 0;
    }
    
    prime_cache.head[prime_cache.length - 1].candidate = val;
    prime_cache.head[prime_cache.length - 1].is_prime = is_prime;

    return 1;
}

int is_prime( unsigned long n )
{
    int cache_check = check_cache( n );

    if( cache_check != 2 )
    {
        return cache_check;
    }

    if( n == 2 || n == 3 )
    {
        return 1;
    }

    if( ( n % 2 == 0 ) || ( n % 3 == 0 ) )
    {
        add_to_cache( n, 0 );
        return 0;
    }

    unsigned long i;
    unsigned long ceil = ( ( unsigned long ) sqrt( n ) + 2 );

    for( i = 6; i < ceil; i = i + 6 )
    {
        if( n % ( i - 1 ) == 0 )
        {
            add_to_cache( n, 0 );
            return 0;
        }

        if( n % ( i + 1 ) == 0 )
        {
            add_to_cache( n, 0 );
            return 0;
        }
    }
    
    add_to_cache( n, 1 );
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

    int * array = ( int * ) malloc( sizeof( int ) * length );

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
    // assumes we are operating from &array from 0 to 4
    int i;

    for( i = 0; i < 5; i++ )
    {
        int j;

        for( j = i + 1; j < 5; j++ )
        {
            if( 0 == is_prime( concatenate_numbers( array[i], array[j] ) ) ) return 0;
            if( 0 == is_prime( concatenate_numbers( array[j], array[i] ) ) ) return 0;
        }
    }

    return 1;
}

void init_with_true( t_item * bitset, int maximum )
{
    int p = maximum / BITS;
    int i;

    for( i = 0; i <= p; i++ )
    {
        bitset[i] = all_true;
    }

    return;
}

t_item contains( t_item * bitset, int i )
{
    return !!( bitset[i / BITS] & (1LL << ( i % BITS ) ) );
}

void discard( t_item * bitset, int i )
{
    bitset[ i / BITS ] &= ~( 1LL << ( i % BITS ) );

    return;
}

int prime_pair_check( int a, int b )
{
    if( is_prime( concatenate_numbers( a, b ) ) != 1 ) return 0;
    if( is_prime( concatenate_numbers( b, a ) ) != 1 ) return 0;

    return 1;
}

void primes( t_item * primes_bitset, int maximum )
{
    int m, km;

    init_with_true( primes_bitset, maximum );

    discard( primes_bitset, 1 );

    for( km = 4; km <= maximum; km += 2 )
    {
        discard( primes_bitset, km );
    }

    for( m = 3; m <= maximum; m += 2 )
    {
        if( contains( primes_bitset, m ) )
        {
            for( km = 2; km <= maximum; km += m )
            {
                discard( primes_bitset, km );
            }
        }
    }

    return;
}

int main()
{
    if( init_prime_cache() == 0 )
    {
        printf( "Failed to init prime cache\n" );
        return 0;
    }

    int maximum = MAX;
    t_item * primes_bitset = ( t_item * ) malloc( maximum + BITS );

    if( &primes_bitset == 0 )
    {
        printf( "Failed to allocate memory for bitmap\n" );
        return 0;
    }

    printf( "Calculating prime bitmap to %d...\n", maximum );
    primes( primes_bitset, maximum );

    int prime_count = 0;
    int n;

    for( n = 1; n <= maximum; n++ )
    {
        if( contains( primes_bitset, n ) )
        {
            prime_count++;
        }
    }

    unsigned long * array = ( unsigned long * ) malloc( prime_count * sizeof( unsigned long ) );
    printf( "Converting prime bitmap\n" );
    if( &array == 0 )
    {
        printf( "Failed to allocate memory for prime array\n" );
        return 0;
    }

    prime_count = 0; // used as index now

    for( n = 1; n <= maximum; n++ )
    {
        if( contains( primes_bitset, n ) )
        {
            array[prime_count] = n;
            prime_count++;
        }
    }
    
    free( primes_bitset );

    int a,b,c,d,e;
    unsigned long av, bv, cv, dv, ev;
    unsigned long current_min = 999999999;
    unsigned long max_prime = array[prime_count - 1];
    
    printf( "Initializing loops\n" ); 
    for( a = 0; a < prime_count; a++ )
    {
        av = array[a];
        printf( "Lead value: %lu\n", av );
        for( b = a + 1; b < prime_count; b++ )
        {
            bv = array[b];
            
            if( prime_pair_check( av, bv ) == 1 )
            {
                for( c = b + 1; c < prime_count; c ++ )
                {
                    cv = array[c];
                    
                    if(
                           prime_pair_check( av, cv ) == 1
                        && prime_pair_check( bv, cv ) == 1
                      )
                    {
                        for( d = c + 1; d < prime_count; d++ )
                        {
                            dv = array[d];
                            
                            if(
                                    ( av + bv + cv + dv ) < current_min
                                 && prime_pair_check( av, dv ) == 1
                                 && prime_pair_check( bv, dv ) == 1
                                 && prime_pair_check( cv, dv ) == 1
                              )
                            {
                                for( e = d + 1; e < prime_count; e++ )
                                {
                                    ev = array[e];
                                    
                                    if(
                                            ( av + bv + cv + dv + ev ) < current_min 
                                         && prime_pair_check( av, ev ) == 1
                                         && prime_pair_check( bv, ev ) == 1
                                         && prime_pair_check( cv, ev ) == 1
                                         && prime_pair_check( dv, ev ) == 1
                                       )
                                    {
                                        printf( "Found min array[ %lu, %lu, %lu, %lu, %lu ]. Sum is %lu\n", av, bv, cv, dv, ev, av+bv+cv+dv+ev );
                                        current_min = av+bv+cv+dv+ev;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf( "The smallest sum I have is %lu\n", current_min );
    free( array );
    return 0;
}
