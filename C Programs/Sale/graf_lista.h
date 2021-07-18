#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int vrh;
    unsigned int kapacitet;
    int *niz;
}Stek;

typedef struct
{
    int velicina;
    int kapacitet;
    int glava;
    int rep;
    int *niz;
}Red;

typedef struct Lista
{
    int vr;
    int tezina;
    struct Lista *sledeci;
}Lista;

typedef struct 
{
    int vr_cvora;
    int stepen_izlazni;
    int stepen_ulazni;
    struct Lista *glava;
}Lista_povezanosti;

typedef struct
{
    int V;
    int *visited;
    Lista_povezanosti *niz;
    Lista_povezanosti* ia;
}Graf;

Stek *napravi_stek( unsigned int kapacitet );

int prazan( Stek *S );

int pun( Stek *S );

void push( int vr , Stek *S );

int pop( Stek *S );

Red *inicijalizuj_red( int kapacitet );

int jel_prazan( Red *r );

int jel_pun( Red *r );

Red *ubaci_u_red( Red *r , int vr );

int izbaci_iz_reda( Red *r );

///////////////////////////////////////////////////////////////////////

Lista *napravi_el( int vr );

Graf *inicijalizuj_graf( int V );

void dodaj_ivicu_neusmeren( Graf *G , int pocetak , int kraj );

void dodaj_ivicu_usmeren( Graf *G , int pocetak , int kraj , int tezina );

void stampaj( Graf *G );

void dubina_pom( Graf *G , int V , int poseceni[] );

void dubina_obilazak( Graf *G , int V );

void dubina_iterativno( Graf *G , int V );

void sirina_iterativno( Graf *G , int V );

int jel_dvostruko_povezan_pomocni( Graf *G , int pocetak , int kraj );

void jel_dvostruko_povezan( Graf *G , int pocetak , int kraj );

int jel_most( Graf *G , int pocetak , int kraj );

int jel_aciklican( Graf *G );

void topoloski_sort( Graf *G );
