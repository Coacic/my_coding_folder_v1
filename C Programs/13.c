#include "13.h"

typedef struct _Stablo
{
	int vr;
	struct _Stablo *levo;
	struct _Stablo *desno;
} Stablo;

Stablo *napravi( int vrednost ) 
{
    Stablo *novo_stablo = ( Stablo * ) malloc( sizeof( Stablo ) );
    if( novo_stablo == NULL ) exit( EXIT_FAILURE );
    
    novo_stablo->vr = vrednost;
    novo_stablo->levo = NULL;
    novo_stablo->desno = NULL;

    return ( novo_stablo );
}

void dodaj_deo( Stablo **koren , int vrednost )
{
    if( !( *koren ) ) *koren = napravi( vrednost );
    else if( ( *koren )->vr > vrednost ) dodaj_deo( &( ( *koren )->levo ) , vrednost );
    else dodaj_deo( &( ( *koren )->desno ) , vrednost );
}

void oslobodi( Stablo **koren )
{
    if( *koren )
    {
        oslobodi( &( ( *koren )->levo ) );
        oslobodi( &( ( *koren )->desno ) );
        
        free( *koren );
        
        *koren = NULL;
    };
}

int max( int a , int b )
{
    if( a > b )return( a );
    else return( b );
}

int dubina( Stablo *koren ) 
{    
    if( !koren ) return( 0 );

    int dubina_levog = dubina( koren->levo );
    int dubina_desnog = dubina( koren->desno );
    
    return( 1 + max( dubina_levog , dubina_desnog ) );
}

void stampaj_nivo( Stablo *koren , int nivo ) 
{ 
    if( !koren ) return; 
    if( nivo == 1 ) printf( "%d " , koren->vr ); 
    else if ( nivo > 1 ) 
    { 
        stampaj_nivo( koren->levo , nivo - 1 ); 
        stampaj_nivo( koren->desno , nivo - 1 ); 
    };
} 

void stampa_po_nivou( Stablo *koren ) 
{ 
    int i , dim = dubina( koren ); 

    for ( i = 1 ; i <= dim ; i++ )
    {
        printf( "%d. nivo stabla:  " , i );
        stampaj_nivo( koren , i ); 
        printf( "\n" );
    };
} 
