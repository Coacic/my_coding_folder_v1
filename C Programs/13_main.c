#include "13.h"

int main( int argc , char **argv )
{
    Stablo *koren = NULL;
    
    int niz[] = { 100 , 50 , 130 , 70 , 140 , 160 , 135 , 80 , 65 };
    int i , dim = sizeof( niz ) / sizeof( int );
    
    for( i = 0 ; i < dim ; i++ ) dodaj_deo( &koren , niz[ i ] );
    
    stampa_po_nivou( koren );
    
    oslobodi( &koren );
    
    return( 0 );
}
