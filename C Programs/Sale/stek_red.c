#include "graf_lista.h"

Stek *napravi_stek( unsigned int kapacitet )
{
    Stek *S = ( Stek * ) malloc( sizeof( Stek ) * kapacitet );
    
    S->vrh = -1;
    S->kapacitet = kapacitet;
    S->niz = ( int * ) malloc( sizeof( int ) * S->kapacitet );
    
    return( S );
}

int prazan( Stek *S )
{
    return( S->vrh == -1 );
}

int pun( Stek *S )
{
    return( S->vrh == S->kapacitet - 1 );
}

void push( int vr , Stek *S )
{
    if( pun( S ) == 1 )
    {
        printf( "Stek je pun!\n" );
        return;
    };
    
    S->niz[ ++S->vrh ] = vr;
}

int pop( Stek *S )
{
    if( prazan( S ) == 1 )
    {
        printf( "Stek je prazan!\n" );
        return( -1 );
    };
    
    return( S->niz[ S->vrh-- ] );
}

Red *inicijalizuj_red( int kapacitet )
{
    Red *novi_el = ( Red * ) malloc( sizeof( Red ) );
    if( !novi_el ) exit( EXIT_FAILURE );
    
    novi_el->kapacitet = kapacitet;
    novi_el->velicina = 0;
    novi_el->glava = 0;
    novi_el->rep = 0;
    novi_el->niz = ( int * ) malloc( sizeof( int ) * kapacitet );
    
    return( novi_el );
}

int jel_prazan( Red *r )
{
    return( r->glava == r->rep );
}

int jel_pun( Red *r )
{
    return( r->velicina == r->kapacitet );
}

Red *ubaci_u_red( Red *r , int vr )
{
    if( jel_pun( r ) ) printf( "Red je pun!\n" );
    else
    {
        r->niz[ r->rep++ ] = vr;
        r->velicina++;
    };
    
    return( r );
}

int izbaci_iz_reda( Red *r )
{
    if( jel_prazan( r ) )
    {
        printf( "Red je prazan!\n" );
        exit( EXIT_FAILURE );
    };
    
    r->velicina--;
    
    return( r->niz[ r->glava++ ] );
}
