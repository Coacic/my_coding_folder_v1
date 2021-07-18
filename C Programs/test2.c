#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *readWords()
{
    char *pom = NULL, c;
    int br = 0, brojac = 0;

    while ((c = getchar()) != '\n')
    {
        pom = realloc(pom, (br + 1) * sizeof(char));
        if (!pom)
        {
            free(pom);
        }
        pom[br] = c;
        br++;
    }
    pom = realloc(pom, (br + 1) * sizeof(char));
    if (!pom)
    {
        free(pom);
    }
    pom[br] = '\0';

    return pom;
}

int main()
{
    int brV = 0, brM = 0, brbr = 0, *n;
    char *rec = readWords();
    for (int i = 0; rec[i] != '\0'; i++)
    {
        if (rec[i] >= 'A' && rec[i] <= 'Z')
        {
            brV++;
        }
        else if (rec[i] >= 'a' && rec[i] <= 'z')
        {
            brM++;
        }
        else if (rec[i] >= 48 && rec[i] <= 58)
        {
            brbr++;
        }
    }

    printf("%s\n", rec);

    printf("%d\n%d\n%d", brV, brM, brbr);
    return 0;
}