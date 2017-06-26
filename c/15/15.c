/*
Starting in the top left corner of a 2x2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20x20 grid?

our 2 x 2 lattice consists of 9 points
x x x
x x x
x x x
at which a decision can be made to go right or down.
on the edges we are limited
0 2 0
2 2 0
0 0 0
*/


#include <stdio.h>

unsigned long trace_path( int, int );

unsigned long trace_path( int grid_h, int grid_v )
{
    unsigned long path_count = 0;

    if( grid_h == 0 | grid_v == 0 )
    {
        return 1;
    }

    if( grid_h > 0 )
    {
        path_count += trace_path( grid_h - 1, grid_v );    
    }

    if( grid_v > 0 )
    {
        path_count += trace_path( grid_h, grid_v - 1 );
    }

    return path_count;
}

void main( void )
{
    unsigned long result;

    int grid_width = 20;
    int grid_height = 20;

    result = trace_path( grid_width, grid_height );

    printf( "Got %lu paths\n", result );
    return;
}
