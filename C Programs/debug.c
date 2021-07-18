#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **loadMap(int *rows)
{
    int m = 0, Velicina = 0, i = 0, j = 0;
    char matrica[256];
    char aa[256];
    char **a, c;
    int *n = rows,
        *br = rows;
    scanf("%d", &m);
    //m=*rows;
    while ((c = getchar()) != '\n')
    {
        if (c != ' ')
        {
            *rows = c;
            rows++;
        }
    }
    
    Velicina = m * 2;
    if (m <= 0)
    {
        return 0;
    }
    /*while(br!=Velicina)
    {
        scanf("%c", &aa[br]);
        matrica[br] = aa[br];
        br++;
    }*/
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("%c", (*br));
            br++;
            //br++;
            if (j < 1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    br = n;
    if (m > 0)
    {
        a = malloc(m * sizeof(int *));
        for (i = 0; i < m; i++)
        {
            a[i] = malloc(2 * sizeof(int));
            for (j = 0; j < 2; j++)
            {
                a[i][j] = *br;
                br++;
            }
        }
    }

    /*for (i=0;i<m;i++){
        free(a[i]);
    }
    free(a);*/
    return a;
}

int main()
{
    int rows[256];
    char **matrica;
    matrica = loadMap(rows);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%c ", matrica[i][j]);
        }
        
    }
    

}