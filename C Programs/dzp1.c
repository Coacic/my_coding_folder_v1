#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define MAX_LENGTH 500

int main()
{
    int n, num, i, j, m = 100, u, kreirana_matrica = 0, x = 0, adresnaFunkcija, Neispravan_Unos = 1, AdresnaFunkcija = 0;
    float usteda_mem, privremena, privremena2;
    int matrica[MAX_LENGTH][MAX_LENGTH];
    int LinearizacijaMatrice[MAX_LENGTH];
    while (2 > 1)
    {
        printf("----------------------------------------------------------------------------------------\n1 : Stvaranje matrice zadatih dimenzija uz inicijalizaciju nepodrazumevanim vrednostima\n2 : Postavljanje podrazumevane vrednosti\n3 : Dohvatanje zadatog elementa, uz proveru validnosti opsega\n4 : Postavljanje vrednosti datom elementu uz proveru validnosti opsega\n5 : Dohvatanje broja nepodrazumevanih vrednosti\n6 : Ispis matrice\n7 : Racunanje ostvarene ustede memorijskog prostora\n8 : Brisanje matrice\n9 : Linearizacija matrice po kolonama\n10. Ispis adresne funkcije po kojoj je ona linearizovana \n0 : Izlaz iz programa\n----------------------------------------------------------------------------------------\n");
        //sleep(2);
        printf("Unesite opciju koji zelite da koriste\n");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            kreirana_matrica = 1;
            printf("n=?\n");
            scanf("%d", &n);
            m = (n - 1) * (n) / 2;
            // Inicijalizacija nepodrazumevanih elemenata
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    matrica[i][j] = 0;
                }
            }
            break;
        case 2:
            if (kreirana_matrica == 0)
            {
                printf("Matrica nije inicijalizovana\n");
                break;
            }
            printf("Unesite %d elemenata za datu strogo trougaonu matricu dimenzije %d\n", m, n);
            // Inicijalizacija podrazumevanih elemenata
            for (int i = 0; i < n; i++)
            {
                for (int j = 1; j < n; j++)
                {
                    if (j > i)
                    {
                        scanf("%d", &matrica[i][j]);
                    }
                }
            }
            printf("Matrica dimenzije %d je uspesno ucitana!\n", n);
            break;
        case 3:
            if (kreirana_matrica == 0)
            {
                printf("Matrica nije inicijalizovana\n");
                break;
            }
            while (2 > 1)
            {
                i = 0;
                j = 0;
                printf("Unesite vrednost i, j datog elementa matrice koji zelite da dohvatite u opsegu od 0 do %d\n", n - 1);
                scanf("%d%d", &i, &j);
                if (i < 0 || i > n - 1 || j < 0 || j > n - 1)
                {
                    printf("Neispravan unos!!\n");
                    Neispravan_Unos = 0;
                }
                if (matrica[i][j] == 0 && Neispravan_Unos == 1)
                {
                    printf("Dohvatili ste nepodrazumevani element matrice\n");
                }
                else
                {
                    break;
                }
            }
            //matrica[0][0] + ((j - 1)* n + i - 1 );
            AdresnaFunkcija = matrica[0][1] + j * (j - 1) / 2 + i - 1;
            printf("Adresna funckija je: %d\n", AdresnaFunkcija);
            printf("Na poziciji %d i %d, na adresi se %x nalazi element: %d\n", i, j, &matrica[i][j], matrica[i][j]);
            break;
        case 4:
            if (kreirana_matrica == 0 || (i > n - 1 || j > n - 1 || j < 0 || i < 0))
            {
                printf("Matrica nije inicijalizovana / Niste uneli vrednosti za i, j.\n");
                break;
            }
            printf("Na mestu %d, %d upisujemo vrednost\n", i, j);
            scanf("%d", &matrica[i][j]);
            break;
        case 5:
            if (kreirana_matrica == 0)
            {
                printf("Matrica nije inicijalizovana\n");
                break;
            }
            u = n * n - ((n - 1) * (n) / 2);
            printf("Broj nepodrazumevanih vrednosti date matrice je: %d\n", u);
            break;
        case 6:
            if (kreirana_matrica == 0)
            {
                printf("Matrica nije inicijalizovana\n");
                break;
            }

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    printf("%4d", matrica[i][j]);
                }
                printf("\n");
            }
            break;
        case 7:
            if (kreirana_matrica == 0)
            {
                printf("Matrica nije inicijalizovana\n");
                break;
            }
            m = (n - 1) * (n) / 2;
            privremena = n * n - m;
            privremena2 = n * n;
            usteda_mem = (privremena / privremena2) * 100;
            printf("ustedeli smo %.0f%% memorijskog prostora.\n", trunc(usteda_mem));
            break;
        case 8:
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    matrica[i][j] = 0;
                }
            }
            printf("Matrica je uspesno obrisana");
            kreirana_matrica = 0;
            break;
        case 9:
            if (kreirana_matrica == 0)
            {
                printf("Matrica nije inicijalizovana\n");
                break;
            }
            x = 0;
            printf("Linearizujemo strogo gornju matricu dimenzije %d:\n", n);
            for (int i = 1; i < n; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    LinearizacijaMatrice[x] = matrica[j][i];
                    printf("%d. Element na poziciji %d i %d je %d\n", x + 1, i, j, LinearizacijaMatrice[x]);
                    x++;
                }
            }
            for (x = 0; x < m; x++)
            {
            }
            printf("\n");
            break;
        case 10:
            printf("Formula adresne funkcije je A[i,j] = A[0,1] + j*(j-1)/2 + i - 1\n");
            break;
        case 0:
            return 0;
        default:
            printf("Pogresna opcija!\n");
            break;
        }
    }
}