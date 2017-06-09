#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libpq-fe.h>
#include <math.h>
#include <string.h>

/*
    Compile with:

gcc this_file.c -I /usr/include/postgresql/ -L /usr/include/postgresql/ -lm -lpq -o this_file 
*/

int main( int argc, char ** argv )
{
    /* Parse command line arguments */
    char * conninfo = NULL;
    char * username = NULL;
    char * dbname   = NULL;
    char * port     = NULL;
    char * hostname = NULL;

    int index;
    int c;

    opterr = 0;

    while( ( c = getopt( argc, argv, "U:p:d:h:" ) ) != -1 )
    {
        switch( c )
        {
            case 'U':
                username = optarg;
                break;
            case 'p':
                port = optarg;
                break;
            case 'd':
                dbname = optarg;
                break;
            case 'h':
                hostname = optarg;
                break;
            default:
                return 1;
        }
    }
   
    /*
        malloc connection string 
        accounting for
        'username=? host=? port=? dbname=?'
    */
    conninfo = ( char * ) malloc(
        sizeof( char ) *
        (
            strlen( username ) +
            strlen( port ) +
            strlen( dbname ) +
            strlen( hostname ) +
            25
        )
    );
 
    /* Assemble the connections string */ 
    strcpy( conninfo, "user=" );
    strcat( conninfo, username );
    strcat( conninfo, " host=" );
    strcat( conninfo, hostname );
    strcat( conninfo, " port=" );
    strcat( conninfo, port );
    strcat( conninfo, " dbname=" );
    strcat( conninfo, dbname );
   
    /* Connect to the database */ 
    PGconn * conn = PQconnectdb( conninfo );

    if( PQstatus( conn ) != CONNECTION_OK )
    {
        fprintf(
            stderr,
            "Connection to database failed: %s\n",
            PQerrorMessage( conn )
        );
        
        PQfinish( conn );
        return 1;
    }
    else
    {
        printf( "Connected to database\n" );
    }

    PGresult * result;

    free( conninfo );
    PQfinish( conn );
    return 0;
}
