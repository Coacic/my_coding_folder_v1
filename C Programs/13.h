#include<stdio.h>
#include<stdlib.h>

typedef struct _Stablo Stablo;

Stablo *napravi( int vrednost );

void dodaj_deo( Stablo **koren , int vrednost );

void oslobodi( Stablo **koren );

int max( int a , int b );

int dubina( Stablo *koren );

void stampaj_nivo( Stablo *koren , int nivo );

void stampa_po_nivou( Stablo *koren );
