#include "graf_lista.h"

int main()
{
	int V = 6, *topologicalSortMatrix = NULL;
	Graf* G1 = inicijalizuj_graf(V);

	dodaj_ivicu_usmeren(G1, 5, 0, 15);
	dodaj_ivicu_usmeren(G1, 3, 0, 20);
	dodaj_ivicu_usmeren(G1, 5, 2, 2);
	dodaj_ivicu_usmeren(G1, 2, 4, 18);
	dodaj_ivicu_usmeren(G1, 4, 1, 9);
	dodaj_ivicu_usmeren(G1, 3, 1, 10);

	stampaj(G1);

	printf("\n---%d---\n", jel_aciklican(G1));
	//          printf( "\n---%d---\n",G1->niz[1].vr_cvora );
	//         topoloski_sort( G1 );

	return(0);
}