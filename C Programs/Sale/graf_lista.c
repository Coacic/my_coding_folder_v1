#include "graf_lista.h"

Lista* napravi_el(int vr)
{
	Lista* novi_el = (Lista*)malloc(sizeof(Lista));
	if (!novi_el) exit(EXIT_FAILURE);

	novi_el->vr = vr;
	novi_el->sledeci = NULL;

	return(novi_el);
}

Graf* inicijalizuj_graf(int V)
{
	int i;

	Graf* G = (Graf*)malloc(sizeof(Graf));
	if (!G) exit(EXIT_FAILURE);

	G->V = V;
	G->niz = (Lista_povezanosti*)malloc(V * sizeof(Lista_povezanosti));

	for (i = 0; i < V; ++i)
	{
		G->niz[i].stepen_izlazni = 0;
		G->niz[i].glava = NULL;
	};

	return(G);
}

void dodaj_ivicu_neusmeren(Graf* G, int pocetak, int kraj)
{
	Lista* novi_el = napravi_el(kraj);
	novi_el->sledeci = G->niz[pocetak].glava;

	G->niz[pocetak].glava = novi_el;
	G->niz[pocetak].stepen_izlazni++;
	G->niz[pocetak].stepen_ulazni++;

	novi_el = napravi_el(pocetak);
	novi_el->sledeci = G->niz[kraj].glava;

	G->niz[kraj].glava = novi_el;
	G->niz[kraj].stepen_izlazni++;
	G->niz[kraj].stepen_ulazni++;
}

void dodaj_ivicu_usmeren(Graf* G, int pocetak, int kraj, int tezina)
{
	Lista* novi_el = napravi_el(kraj);
	novi_el->sledeci = G->niz[pocetak].glava;

	G->niz[kraj].vr_cvora = kraj;
	G->niz[kraj].stepen_ulazni++;

	G->niz[pocetak].vr_cvora = pocetak;
	G->niz[pocetak].glava = novi_el;
	G->niz[pocetak].glava->tezina = tezina; //tezina za usmerene grafove (tezinski graf)
	G->niz[pocetak].stepen_izlazni++;
}

int jel_dvostruko_povezan_pomocni(Graf* G, int pocetak, int kraj) //provera za date el da li su dvostruko povezani
{
	Lista* pom = G->niz[pocetak].glava;
	int ind1 = 0, ind2 = 0;

	while (pom && !ind1)
	{
		if (pom->vr == kraj) ind1 = 1;
		else pom = pom->sledeci;
	};

	pom = G->niz[kraj].glava;

	while (pom && !ind2)
	{
		if (pom->vr == pocetak) ind2 = 1;
		else pom = pom->sledeci;
	};

	return(ind1 + ind2);
}

void jel_dvostruko_povezan(Graf* G, int pocetak, int kraj)
{
	int rez = jel_dvostruko_povezan_pomocni(G, pocetak, kraj);

	if (rez == 2) printf("\nElement %d je dvostruko povezan sa elementom %d\n", pocetak, kraj);
	else printf("\nElement %d nije dvostruko povezan sa elementom %d\n", pocetak, kraj);
}

int jel_most(Graf* G, int pocetak, int kraj)
{
	Lista* pom = G->niz[pocetak].glava;
	int brojac = 0;

	while (pom)
	{
		if (pom->vr == kraj) brojac++;
		pom = pom->sledeci;
	};

	if (brojac == 1 && jel_dvostruko_povezan_pomocni(G, pocetak, kraj) != 2) return(1);
	else return(0);
}

int jel_aciklican(Graf* G)
{
	int i;

	for (i = 0; i < G->V; i++)
	{
		Lista* pom = G->niz[i].glava;

		while (pom)
		{
			if (!jel_most(G, i, pom->vr)) return(0);
			else pom = pom->sledeci;
		};
	};

	return(1);
}

void stampaj(Graf* G)
{
	int i;

	for (i = 0; i < G->V; i++)
	{
		Lista* pom = G->niz[i].glava;

		printf("\nLista povezanosti za cvor %d\n Glava ", i);

		while (pom)
		{
			printf("-> %d", pom->vr);
			pom = pom->sledeci;
		};

		printf("\n");
	};
}

void dubina_pom(Graf* G, int V, int poseceni[])
{
	Lista* i;

	poseceni[V] = 1;

	printf("%d ", V);

	for (i = G->niz[V].glava; i; i = i->sledeci) if (poseceni[i->vr] != 1) dubina_pom(G, i->vr, poseceni);
}

void dubina_obilazak(Graf* G, int V)
{
	int* poseceni = (int*)calloc(G->V, sizeof(int));

	dubina_pom(G, V, poseceni);
}

void dubina_iterativno(Graf* G, int V)
{
	Stek* S = napravi_stek(G->V);
	Lista* i;
	int pom, * poseceni = (int*)calloc(G->V, sizeof(int));

	push(V, S);

	printf("\n\nCvorovi se po dubini obilaze sledecim redom:\n");

	while (!prazan(S))
	{
		pom = pop(S);

		if (!poseceni[pom])
		{
			printf("%d ", pom);
			poseceni[pom] = 1;
		};

		i = G->niz[pom].glava;

		while (i)
		{
			if (!poseceni[i->vr]) push(i->vr, S);
			i = i->sledeci;
		};
	};

	printf("\n");
}

void sirina_iterativno(Graf* G, int V)
{
	Red* R = inicijalizuj_red(G->V);
	Lista* i;
	int pom, * poseceni = (int*)calloc(G->V, sizeof(int));

	R = ubaci_u_red(R, V);

	printf("\n\nCvorovi se po sirini obilaze sledecim redom:\n");

	while (!jel_prazan(R))
	{
		pom = izbaci_iz_reda(R);

		if (!poseceni[pom])
		{
			printf("%d ", pom);
			poseceni[pom] = 1;
		};

		i = G->niz[pom].glava;

		while (i)
		{
			if (!poseceni[i->vr]) R = ubaci_u_red(R, i->vr);
			i = i->sledeci;
		};
	};

	printf("\n");
}


void topoloski_sort(Graf* G)
{
	Stek* S1 = napravi_stek(G->V), * S2 = napravi_stek(G->V);
	int ind = 0, pom1, * poseceni = (int*)calloc(G->V, sizeof(int));
	Lista* pom;

	while (ind < G->V && pun(S1) == 0)
	{
		if (G->niz[ind].glava == NULL)
		{
			poseceni[ind] = 1;

			if (pun(S1) == 0) push(G->niz[ind].vr_cvora, S1);

			ind++;
		}
		else
		{
			pom = G->niz[ind].glava;

			while (pom)
			{
				if (pom->sledeci == NULL || poseceni[pom->sledeci->vr] != 0)
				{
					poseceni[pom->vr] = 1;

					if (pun(S1) == 0) push(pom->vr, S1);
					if (prazan(S2) == 0) pom1 = pop(S2);
					else pom1 = -1;

					if (pom1 != -1) pom = G->niz[pom1].glava;
					else ind++;
				}
				else if (poseceni[pom->sledeci->vr] == 0)
				{
					if (pun(S2) == 0) push(pom->vr, S2);
					pom = G->niz[pom->sledeci->vr].glava;
				}
				else pom = pom->sledeci;
			};

			if (pom == NULL && pun(S1) == 0)
			{
				push(G->niz[ind].vr_cvora, S1);
				ind++;
			}
		};
	};

	while (!prazan(S1)) printf("%d ", pop(S1));
}


